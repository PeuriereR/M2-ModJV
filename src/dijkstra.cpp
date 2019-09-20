#include "dijkstra.h"

Dijkstra::Dijkstra()
{

}

void Dijkstra::changeHF(){
    std::vector<Vec2> Voisin = fillVoisin(2);

    QVector<float> height;
    for(unsigned int i = 0; i < path.size();i++){
        height.push_back(Hf.value(path[i].x(),path[i].y()));
    }

    for(unsigned int i = 0; i < path.size();i++){
        for(unsigned int j = 0; j < Voisin.size(); j++){
            if(Hf.inSF2(path[i].x()+Voisin[j].x(),path[i].y()+Voisin[j].y()))
                Hf.putValue(path[i]+Voisin[j],height[i]);
        }
    }
}

void Dijkstra::addNeighborToPath(){
     std::vector<Vec2> Voisin = fillVoisin(1);
     int size = path.size();
     for(int i = 0; i < size;i++){
         for(unsigned int j = 0; j < Voisin.size(); j++){
             if(Hf.inSF2(path[i].x()+Voisin[j].x(),path[i].y()+Voisin[j].y())){
                 bool contains = false;
                 for(unsigned int k = 0; k < path.size();k++){
                     if(path[k] == path[i]+Voisin[j]){
                        contains = true;
                        break;
                     }
                 }
                 if(!contains)
                    path.push_back(path[i]+Voisin[j]);
             }
         }
     }
}

void Dijkstra::objForests(){
    for(unsigned int i = 0; i < forests.size();i++){
        forests[i].objForest(QString("forestRoad")+QString::number(i)+QString(".obj"));
    }
}


void Dijkstra::clearForests(){
    float maxHeight, minHeight;
    Hf.getRange(minHeight,maxHeight);
    for(unsigned int i = 0; i < forests.size();i++)
    {
        for(unsigned int j = 0; j < path.size();j++)
        {
            for(unsigned int k = 0; k < forests[i].forest.pos.size(); k++)
            {
                if(forests[i].forest.pos[k] == path[j] || (Hf.value(forests[i].forest.pos[k])+ abs(minHeight)) / (abs(minHeight) + maxHeight) < 0.15){
                    forests[i].forest.pos.erase(forests[i].forest.pos.begin()+k);
                    forests[i].forest.age.erase(forests[i].forest.age.begin()+k);
                    k--;
                }
            }
        }
    }
}

std::vector<Vec2> Dijkstra::fillVoisin(int size){
    std::vector<Vec2> Voisin;
    for(int j = - size; j < size + 1; j++){
        for(int k = - size; k < size + 1; k++){
            if( (abs(j) < 2 && abs(k) < 2) || j == 0 || k == 0)
            Voisin.push_back(Vec2(j,k));
        }
   }


    return Voisin;
}


Dijkstra::Dijkstra(HeightField hf, std::vector<Veget> forestsTemp,QVector<Vec2> spots, int center){
    Hf = hf;
    forests = forestsTemp;
    std::vector<Vec2> Voisin = fillVoisin(1);

    float maxHeight, minHeight;
    hf.getRange(minHeight,maxHeight);
    Vec2 lim(hf.nx(),hf.ny());
    adjacency_list_t adjacency_list(lim.x()*lim.y());
    for(int i = 0; i < lim.x(); i++)
    {
        for(int j = 0; j < lim.y();j++){
            int height = floor(hf.value(i,j));
            int index = hf.index(i,j);
            for(unsigned int k = 0; k < Voisin.size();k++){
                int x = i + Voisin[k].x();
                int y = j + Voisin[k].y();
                if(hf.inSF2(x,y)){
                    int heightVoisin = floor(hf.value(x,y));
                    int indexVoisin = hf.index(x,y);
                    int distance = ((x-i)*(x-i) + (y-j)*(y-j));
                    int diffH = abs(height - heightVoisin);

                    float waterImpact = (height + abs(minHeight)) / (abs(minHeight) + maxHeight) > 0.25 ? 1 : 10 ;
                    int cost = diffH * waterImpact * 50 + distance ;
                    adjacency_list[index].push_back(neighbor(indexVoisin,cost));
                }

            }
        }
    }

    std::vector<float> min_distance;
    std::vector<int> previous;
    DijkstraComputePaths(hf.index(spots[center].x(),spots[center].y()), adjacency_list, min_distance, previous);

    for(int i = 0; i < spots.size();i++){
        if(i != center){
            std::vector<int> pathIndex = DijkstraGetShortestPathTo(hf.index(spots[i].x(),spots[i].y()), previous);

            for(unsigned int i = 0; i < pathIndex.size();i++){
                path.push_back(hf.posFromIndex(pathIndex[i]));
            }
        }
    }

    addNeighborToPath();
    changeHF();
    clearForests();

}


QImage Dijkstra::drawPath(QImage image){
    for(unsigned int i = 0; i < path.size();i++){
        image.setPixel(path[i].x(),path[i].y(), qRgb(255,0,0));
    }
    return image;
}

int Dijkstra::getForestImpact(Vec2 pos,std::vector<Veget> forests){
    for(unsigned int i = 0; i < forests.size();i++){
        for(unsigned int j = 0; j < forests[i].forest.pos.size();j++){
            if(Vec2(forests[i].forest.pos[j].x()-pos.x(),forests[i].forest.pos[j].y()-pos.y()).length() < forests[i].forest.GetRadius(j) * 10)
                return 4;
        }
    }
    return 1;
}


int Dijkstra::findSpotNearCenter(QVector<Vec2> spots,HeightField hf){
    float distanceMin = hf.nx() * hf.ny();
    Vec2 center(hf.nx()/2,hf.ny()/2);
    int index = -1;
    for(int i = 0; i < spots.size();i++){
        float distance = Vec2(spots[i].x()-center.x(),spots[i].y()-center.y()).length() ;
        if(distance< distanceMin){
            distanceMin = distance;
            index = i;
        }
    }

    return index;
}

std::vector<int> Dijkstra::DijkstraGetShortestPathTo(int vertex, const std::vector<int> &previous){
    std::vector<int> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_back(vertex);
    return path;
}


void Dijkstra::DijkstraComputePaths(int source,const adjacency_list_t &adjacency_list,
                          std::vector<float> &min_distance,
                          std::vector<int> &previous){
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<float, int> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        float dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
    const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            int v = neighbor_iter->target;
            float weight = neighbor_iter->weight;
            float distance_through_u = dist + weight;
        if (distance_through_u < min_distance[v]) {
            vertex_queue.erase(std::make_pair(min_distance[v], v));

            min_distance[v] = distance_through_u;
            previous[v] = u;
            vertex_queue.insert(std::make_pair(min_distance[v], v));

        }

        }
    }
}


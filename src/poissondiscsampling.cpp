#include "poissondiscsampling.h"
#include <QDebug>

PoissonDiscSampling::PoissonDiscSampling(int r_p, int k_p, int height_p, int width_p) : r(r_p),k(k_p),height(height_p), width(width_p) {
    srand(time(NULL));
    w = r / sqrt(2);

    // STEP 0
    cols = floor(width / w);
    rows = floor(height / w);
    grid.resize(cols*rows);
    for (int i = 0; i < cols * rows; i++) {
        grid[i].c = Vec2(-1, -1);
    }
}

inline int PoissonDiscSampling::index(int i, int j) {
    return i + j * cols;
}

void PoissonDiscSampling::sampling() {
    // STEP 1 : Init sampling

    // random sample in the image
    int x = rand()%width;
    int y = rand()%height;
    Vec2 init_sample(x,y);
    Disc init_disc(init_sample,r/2);

    int i = floor(x / w); // pos.x (cell) in the grid
    int j = floor(y / w); // pos.y (cell) in the grid

    grid[index(i,j)] = init_disc;
    active.push_back(init_sample);

    // STEP 2 : Process

    int randIndex,neighborIndex, col,row;
    bool found_point, notInDisc;
    float random_pi,random_r,point_x,point_y;
    Vec2 generated_point;
    Disc generated_disc, neighbor;

    while(!active.empty()){

        randIndex = rand()%active.size();
        Vec2 picked_sample = active[randIndex];
        found_point = false;

        for(int n=0; n<k; n++){

            random_pi = ((float)rand() / RAND_MAX) * ( M_PI * 2 );
            random_r = ((float)rand() / RAND_MAX) * r + r;
            point_x = cos(random_pi) * random_r;
            point_y = sin(random_pi) * random_r;

            generated_point = Vec2(picked_sample.x() + point_x, picked_sample.y() + point_y);
            generated_disc = Disc(generated_point,r/2);

            col = floor(generated_point.x() / w);
            row = floor(generated_point.y() / w);

            if(col>=0 && col<cols && row>=0 && row<rows){

                notInDisc = true;
                for(int i=-1; i<=1; i++){
                    for (int j = -1; j <=1 ; j++) { // <=>  &&  grid[col + row*cols].x==-1 quand  i j=0 > case deja occupee

                        neighborIndex = index(col+i,row+j);
                        if (neighborIndex>=0 && neighborIndex<grid.length()){
                            neighbor = grid[neighborIndex];
                            if(neighbor.c.x()!=-1){
                                if(neighbor.intersect(generated_disc)){
                                    notInDisc = false;
                                }
                            }
                        }
                    }
                }
                if (notInDisc){
                    grid[index(col,row)] = generated_disc;
                    active.push_back(generated_point);
                    found_point=true;
                    break;
                }
            }
        }
        if(!found_point){
            active.remove(randIndex);
        }
    }
}

QVector<Vec2> PoissonDiscSampling::getPoints(){
    QVector<Vec2> distrib;
    for (int i = 0; i < grid.size(); ++i) {
        if( grid[i].c.x() >= 0 && grid[i].c.y() >= 0 ) distrib.push_back(Vec2(floor(grid[i].c.x()),floor(grid[i].c.y())));
    }
    return distrib;
}

void PoissonDiscSampling::draw(QImage &img)  {
    QVector<Vec2> point = getPoints();
    for(int i = 0; i < point.size(); ++i) {
        img.setPixel(point[i].x(), point[i].y(), qRgb(0,255,0));
    }
}

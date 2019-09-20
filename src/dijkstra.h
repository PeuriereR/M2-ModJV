#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <list>

#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <iostream>
#include <QDebug>
#include "heightfield.h"
#include "veget.h"
struct neighbor { // chemin jusqu'à un voisin
    int target; // index d'arrivée du chemin
    float weight; // poid du chemin
    neighbor(int arg_target, float arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

const float max_weight = std::numeric_limits<float>::infinity();


class Dijkstra
{
    //Ensemble de position dans le terrain en cercle de taille size autour d'un point
    std::vector<Vec2> fillVoisin(int size);
    //trouve la ville la plus proche du centre
    int findSpotNearCenter(QVector<Vec2> spots,HeightField hf);
    //En fonction d'une position, récupère le type de terrain
    int getForestImpact(Vec2 pos,std::vector<Veget> forests);
    //Toutes les positions des routes
    std::vector<Vec2> path;
    HeightField Hf;
    std::vector<Veget> forests;
public:
    //Constructeur
    Dijkstra();
    Dijkstra(HeightField hf,std::vector<Veget> forestsTemp ,QVector<Vec2> spots,int center);

    //Récupère toutes les positions du chemin de l'origine à vertex
    std::vector<int> DijkstraGetShortestPathTo(int vertex, const std::vector<int> &previous);
    //Calcul en chaque point du terrain la distance minimum depuis une position du terrain
    void DijkstraComputePaths(int source,const adjacency_list_t &adjacency_list,
                              std::vector<float> &min_distance,
                              std::vector<int> &previous);
    //Dessine sur une image les routes
    QImage drawPath(QImage image);
    //Exporte toutes les forets en .obj
    void objForests();
    //Supprime les arbres sur les routes
    void clearForests();
    //Edite le terrain pour aplatir les routes
    void changeHF();
    //Ajoute les voisins de chaque position du chemin à path
    void addNeighborToPath();

    //get
    Veget getForest(int i){return forests[i];}    
    HeightField getHF(){return Hf;}
    std::vector<Vec2> getPath(){return path;}


};

#endif // DIJKSTRA_H

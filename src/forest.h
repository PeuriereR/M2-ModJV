#ifndef FOREST_H
#define FOREST_H

#include "heightfieldmulti.h"
#include <QLabel>

class Forest
{
    //taille du terrain
    Vec2 lim;
    //Probilité de mourrir en fonction de l'âge
    float probaDeath(int age);
public:
    //Constructeur
    Forest();
    //Position des arbres
    std::vector<Vec2> pos;
    //Age des arbres
    std::vector<int> age;

    //Rayon de la taille d'un arbre en fonction de son âge
    float GetRadius(int tree);
    //Récupère une position aléatoire dans un rayon compris entre le rayon de l'arbre et une certaine distance
    float RandomSeed(int tree);
    //Supprime les arbres dont les rayons se touchent (supprime le plus jeune)
    void SelfClear();
    //Effectue un pas de simulation
    void Step();

    void SetLimite(Vec2 limite);
    };

#endif // FOREST_H

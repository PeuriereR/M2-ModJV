#ifndef GRID2_H
#define GRID2_H

#include "box2.h"

// Classe représentant une grille 2D

class Grid2
{
protected:
    Box2 _b2; // Taille réelle de la grille
    int _nx,_ny; // Nombres de cases (nx,ny)
public:
    Grid2(){}
    Grid2(Box2 b2, int nx, int ny);

    Vec2 point(const int &i, const int &j)const;
    // Retourne le vecteur dans le repère du monde de la diagonale d'une case
    Vec2 unitDiagonal() const;

    // Getters
    int nx() const;
    int ny() const;
    Box2& b2();

    // Retourne 8 voisins
    void getNeighbors(Vec2 v, int neighbors[8]);

};

#endif // GRID2_H

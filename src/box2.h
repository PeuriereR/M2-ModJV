#ifndef BOX2_H
#define BOX2_H

#include "vec2.h"

// Classe représentant une boîte 2D

class Box2
{
    // Vecteurs min max
    Vec2 _pmin,_pmax;

public:
    Box2(){}
    Box2(Vec2 pmin, Vec2 pmax);

    // Fonctions de base
    bool inside(const Vec2 &p)const;
    bool intersect(const Box2 &b) const;

    // Getter
    Vec2 pmin() const;
    Vec2 pmax() const;
};

#endif // BOX2_H

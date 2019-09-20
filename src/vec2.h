#ifndef VEC2_H
#define VEC2_H

#include <math.h>

// Classe représentant un vecteur 2D

class Vec2
{
    float _x,_y;

public:
    Vec2(){}
    Vec2(float i, float j);

    void scale(float i, float j);
    void scale(const Vec2& v);
    float dotProduct(const Vec2 &v2) const;
    float length() const;
    void normalize();

    float x() const;
    float y() const;

friend    Vec2 operator +(const Vec2& v, const float k);
friend    Vec2 operator *(const Vec2& v, const float k);
friend    Vec2 operator -(const Vec2& v, const float k);
friend    Vec2 operator /(const Vec2& v, const float k);
friend    Vec2 operator -(const Vec2& v1, const Vec2 v2);
friend    Vec2 operator +(const Vec2& v1, const Vec2 v2);
friend    bool operator ==(const Vec2& v1,const Vec2 v2);
friend    bool operator !=(const Vec2& v1,const Vec2 v2);

};


#endif // VEC2_H

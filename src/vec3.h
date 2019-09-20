#ifndef VEC3_H
#define VEC3_H

#include <math.h>

// Classe représentant un vecteur 3D

class Vec3
{
    float _x,_y,_z;
public:
    Vec3();
    Vec3(float i, float j,float k);

    void scale(float i, float j,float k);
    void scale(const Vec3& v);
    float dotProduct(const Vec3 &v3) const;
    float length() const;
    void normalize();

    float x() const;
    float y() const;
    float z() const;

friend    Vec3 operator +(const Vec3& v, const float k);
friend    Vec3 operator *(const Vec3& v, const float k);
friend    Vec3 operator -(const Vec3& v, const float k);
friend    Vec3 operator /(const Vec3& v, const float k);
friend    Vec3 operator -(const Vec3& v1, const Vec3 v2);
friend    Vec3 operator +(const Vec3& v1, const Vec3 v2);
friend    bool operator ==(const Vec3& v1, const Vec3 v2);
friend    bool operator !=(const Vec3& v1, const Vec3 v2);
};

#endif // VEC3_H

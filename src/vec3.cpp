#include "vec3.h"

Vec3::Vec3(): _x(0), _y(0), _z(0){}

Vec3::Vec3(float i, float j,float k): _x(i), _y(j),_z(k){}


void Vec3::scale(float i, float j,float k){
    _x *= i;
    _y *= j;
    _z *= k;
}

void Vec3::scale(const Vec3& v){
    scale(v.x(),v.y(),v.z());
}

float Vec3::dotProduct(const Vec3 &v) const{
    return _x * v._x + _y * v._y + _z * v._z;
}

float Vec3::length() const{
    return sqrt(_x*_x + _y*_y + _z*_z);
}

void Vec3::normalize(){
    _x /= length();
    _y /= length();
    _z /= length();
}

float Vec3::x() const{
    return _x;
}

float Vec3::y() const{
    return _y;
}

float Vec3::z() const{
    return _z;
}

Vec3 operator +(const Vec3& v, const float k){
    return Vec3(v.x() + k,v.y() + k,v.z() + k);
}

Vec3 operator -(const Vec3& v, const float k){
    return Vec3(v.x() - k,v.y() - k,v.z() - k);
}

Vec3 operator *(const Vec3& v, const float k){
    return Vec3(v.x() * k,v.y() * k,v.z() *k);
}

Vec3 operator /(const Vec3& v, const float k){
    return Vec3(v.x() / k,v.y() / k,v.z() / k);
}

Vec3 operator -(const Vec3& v1, const Vec3 v2){
    return Vec3(v1.x()-v2.x(),v1.y()-v2.y(),v1.z()-v2.z());
}

Vec3 operator +(const Vec3& v1, const Vec3 v2){
    return Vec3(v1.x()+v2.x(),v1.y()+v2.y(),v1.z()+v2.z());
}

bool operator ==(const Vec3& v1, const Vec3 v2){
    return ( (v1.x() == v2.x()) && (v1.y() == v2.y()) && (v1.z() == v2.z()) );
}

bool operator !=(const Vec3& v1, const Vec3 v2){
    return ( (v1.x() != v2.x()) || (v1.y() != v2.y()) || (v1.z() != v2.z()) );
}



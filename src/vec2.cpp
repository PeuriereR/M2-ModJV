#include "vec2.h"

Vec2::Vec2(float i, float j): _x(i), _y(j){}


void Vec2::scale(float i, float j){
    _x *= i;
    _y *= j;
}

void Vec2::scale(const Vec2& v){
    scale(v.x(),v.y());
}

float Vec2::dotProduct(const Vec2 &v2) const{
    return _x * v2._x + _y * v2._y;
}

float Vec2::length() const{
    return sqrt(_x*_x + _y*_y);
}

void Vec2::normalize(){
    _x /= length();
    _y /= length();
}

float Vec2::x() const{
    return _x;
}

float Vec2::y() const{
    return _y;
}

Vec2 operator +(const Vec2& v, const float k){
    return Vec2(v.x() + k,v.y() + k);
}

Vec2 operator -(const Vec2& v, const float k){
    return Vec2(v.x() - k,v.y() - k);
}

Vec2 operator *(const Vec2& v, const float k){
    return Vec2(v.x() * k,v.y() * k);
}

Vec2 operator /(const Vec2& v, const float k){
    return Vec2(v.x() / k,v.y() / k);
}

Vec2 operator -(const Vec2& v1, const Vec2 v2){
    return Vec2(v1.x() - v2.x(),v1.y() - v2.y());
}

Vec2 operator +(const Vec2& v1, const Vec2 v2){
    return Vec2(v1.x() + v2.x(),v1.y() + v2.y());

}

bool operator ==(const Vec2& v1, const Vec2 v2){
    return ( (v1.x() == v2.x()) && (v1.y() == v2.y()) );
}

bool operator !=(const Vec2& v1, const Vec2 v2){
    return ( (v1.x() != v2.x()) || (v1.y() != v2.y()) );
}

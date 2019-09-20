#include "box2.h"

Box2::Box2(Vec2 pmin, Vec2 pmax):_pmin(pmin),_pmax(pmax){}

bool Box2::inside(const Vec2 &p)const{
    if( p.x() > _pmin.x() && p.x() < _pmin.x() && p.y() > _pmin.y() && p.y() < _pmax.y())
        return true;
    return false;
}
bool Box2::intersect(const Box2 &b) const{
    return ( inside(b._pmin) || inside(b._pmax) || inside(Vec2(b._pmin.x(),b._pmax.y())) || inside(Vec2(b._pmax.x(),b._pmin.x())) );
}

Vec2 Box2::pmin() const{
    return _pmin;
}

Vec2 Box2::pmax() const{
    return _pmax;
}

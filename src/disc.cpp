#include "disc.h"

Disc::Disc() : c(Vec2(0, 0)), r(0) {}

Disc::Disc(Vec2 _c, float _r) : c(_c), r(_r) {}

bool Disc::inDisc(Vec2 v) {
    if ((v-c).length()<r)
        return true;
    return false;
}

bool Disc::intersect(Disc d) {
    if ((d.c-c).length()<d.r+r)
        return true;
    return false;
}

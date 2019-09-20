#include "analyticfield.h"

AnalyticField::AnalyticField(){}

HeightField AnalyticField::getHeightField(Box2 b2, int nx, int ny){
    HeightField hf(b2,nx,ny);
    for (int x = 0; x < nx; ++x) {
        for (int y = 0; y < ny; ++y) {
            hf.putValue(x,y,getH(hf.point(x,y)));
        }
    }

    return hf;
}

float AnalyticField::getH(const Vec2& v) const{
    return 0.0;
}

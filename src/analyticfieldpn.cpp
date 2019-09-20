  #include "analyticfieldpn.h"

PerlinNoise AnalyticFieldPN::pn;

AnalyticFieldPN::AnalyticFieldPN(){}

float AnalyticFieldPN::getH(const Vec2 &v) const{
        return pn.noise(v);
}

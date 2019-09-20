#include "analyticfieldsumpn.h"

PerlinNoise AnalyticFieldSumPN::pn;

AnalyticFieldSumPN::AnalyticFieldSumPN(){}


AnalyticFieldSumPN::AnalyticFieldSumPN(float a, float l, int o, float f): amplitude(a), lambda(l), octave(o), facteur(f){}

float AnalyticFieldSumPN::getH(const Vec2 &v) const{
    float a  = amplitude;
    float l = lambda;
    float z = 0;

    // Somme de bruit
    for (int i = 0; i < octave; ++i) {
        z+= pn.noise(v/l)*a;
        a *= facteur;
        l *= facteur;

        // v = rota*v
        // rota > angle rond type 39°
    }
    return z;
}

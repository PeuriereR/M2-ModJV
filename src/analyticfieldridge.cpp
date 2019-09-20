#include "analyticfieldridge.h"

PerlinNoise AnalyticfieldRidge::pn;

AnalyticfieldRidge::AnalyticfieldRidge(){}

AnalyticfieldRidge::AnalyticfieldRidge(float a, float l, int o, float f):amplitude(a), lambda(l), octave(o), facteur(f){}

float AnalyticfieldRidge::getH(const Vec2 &v) const{

    // METHODE 1 & 2 pas terrible

    //    float z_1 = spn.getH(v);

    //    float angle = 91;

    //    Vec2 v3( cos(angle*M_PI/180)*v.x() - sin(angle*M_PI/180)*v.x(),
    //             sin(angle*M_PI/180)*v.y() + cos(angle*M_PI/180)*v.y()
    //             );

    //    Vec2 v2( (int)(v3.x()+170) %500,
    //             (int)(v3.y()+170) %500);

    //    float z_2 = spn.getH(v);
    //    return qMin(z_1,z_2);


    float a  = amplitude;
    float l = lambda;
    float z = 0;

    // 1ere Somme de Perlin Noise
    for (int i = 0; i < octave; ++i) {
        z+= pn.noise(v/l)*a;
        // Approximation de l'atténuation
        if(z<-20 && a<10) a *= 0.8;
        a *= facteur;
        l *= facteur;
    }


    a = amplitude;
    l = lambda;
    float z2 = 0;

    // 2e Somme de Perlin Noise (seed différente)
    for (int i = 0; i < octave; ++i) {
        z2+= pn.noiseShuffle(v/l)*a;
        // Approximation de l'atténuation
        if(z2<-20 && a<10) a *= 0.8;
        a *= facteur;
        l *= facteur;
    }

    // Minimum pour les ridges
    float val = qMin(z,z2);
    return val;
}

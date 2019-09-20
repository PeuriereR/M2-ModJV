#ifndef ANALYTICFIELDRIDGE_H
#define ANALYTICFIELDRIDGE_H

#include "analyticfield.h"
#include "perlinnoise.h"

// Classe pour la création de terrain par Somme de Perlin Noise et Ridge

class AnalyticfieldRidge : public AnalyticField
{
    // Perlin Noise
    static PerlinNoise pn;

    // Variables de la somme
    float amplitude;
    float lambda;
    int octave;
    float facteur;

public:
    AnalyticfieldRidge();
    AnalyticfieldRidge(float a, float l, int o, float f);

    float getH(const Vec2 &v) const;
};

#endif

#ifndef ANALYTICFIELDSUMPN_H
#define ANALYTICFIELDSUMPN_H

#include "analyticfield.h"
#include "perlinnoise.h"

// Classe pour la création de terrain par Somme de Perlin Noise

class AnalyticFieldSumPN : public AnalyticField
{
    // Perlin Noise
    static PerlinNoise pn;

    // Variables de la somme
    float amplitude;
    float lambda;
    int octave;
    float facteur;

public:
    AnalyticFieldSumPN();
    AnalyticFieldSumPN(float a, float l, int o, float f);

    float getH(const Vec2 &v) const;
};

#endif // ANALYTICFIELDSUMPN_H


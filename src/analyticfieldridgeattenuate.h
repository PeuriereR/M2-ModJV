#ifndef ANALYTICFIELDRIDGEATTENUATE_H
#define ANALYTICFIELDRIDGEATTENUATE_H

#include "analyticfield.h"
#include "perlinnoise.h"

// Classe pour la création de terrain par Somme de Perlin Noise, Ridge et Attenuation

class AnalyticFieldRidgeAttenuate : public AnalyticField
{
    // Perlin Noise
    static PerlinNoise pn;

    // Variables de la somme
    float amplitude;
    float lambda;
    int octave;
    float facteur;

public:
    AnalyticFieldRidgeAttenuate();
    AnalyticFieldRidgeAttenuate(float a, float l, int o, float f);

    float getH(const Vec2 &v) const;
};

#endif // ANALYTICFIELDRIDGEATTENUATE_H

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "vec2.h"

// Classe extraite de Rosetta Code
// http://www.rosettacode.org/wiki/Rosetta_Code

class PerlinNoise
{
    static int p[256];
    // 2e seed (1ere mélangée) pour les ridges
    static int pShuffle[256];

public:
    PerlinNoise();
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    double noise(double x, double y, double z);
    double noiseShuffle(double x, double y, double z);
    double noise(const Vec2& v);
    double noiseShuffle(const Vec2& v);
};

#endif // PERLINNOISE_H

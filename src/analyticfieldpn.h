#ifndef ANALYTICFIELDPN_H
#define ANALYTICFIELDPN_H

#include "analyticfield.h"
#include "perlinnoise.h"

// Classe pour la création de terrain par Perlin Noise

class AnalyticFieldPN : public AnalyticField
{
    static PerlinNoise pn;
public:
    AnalyticFieldPN();

    virtual float getH(const Vec2 &v) const;
};

#endif // ANALYTICFIELDPN_H

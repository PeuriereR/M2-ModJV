#ifndef ANALYTICFIELD_H
#define ANALYTICFIELD_H

#include "heightfield.h"

// Classe virtuelle pour la création de terrain

class AnalyticField
{
public:
    AnalyticField();

    // Fonction à dériver pour obtenir une hauteur selon une position
    virtual float getH(const Vec2& v) const;

    // Retourne le HeightField associé
    HeightField getHeightField(Box2 b2, int nx, int ny);
};

#endif // ANALYTICFIELD_H

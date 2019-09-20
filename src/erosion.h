#ifndef EROSION_H
#define EROSION_H

#include "heightfieldmulti.h"

// Classe virtuelle pour l'application d'érosion

class Erosion
{
public:
    Erosion();

    // Types d'érosion
    void slopeErosion(HeightFieldMulti& hfm, float maxHeight);
    void globalErosion(HeightFieldMulti& hfm, float factor);
    // void visibilityErosion(HeightFieldMulti& hfm);

    // Fonction de transfert
    float transfer(float value, float maxHeight);

    // Méthode de transport à dériver
    virtual void carriage(HeightFieldMulti& hfm, int iterations) = 0;
};

#endif // EROSION_H

#ifndef HYDROEROSION_H
#define HYDROEROSION_H

#include "erosion.h"

// Classe pour l'application d'érosion hydraulique

class HydroErosion : public Erosion
{
    // Force du StreamPower / dt
    float k = 0.01;
public:
    HydroErosion();

    // Méthode de transport
    void carriage(HeightFieldMulti& hfm, int iterations);
};

#endif // HYDROEROSION_H

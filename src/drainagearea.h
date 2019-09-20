#ifndef DRAINAGEAREA_H
#define DRAINAGEAREA_H

#include "heightfieldmulti.h"

// Classe stockant les valeurs d'aire de drainage

class DrainageArea: public ScalarField2
{
public:
    // Constructeurs
    DrainageArea();
    DrainageArea(Box2 b2, int nx, int ny);
    DrainageArea(HeightFieldMulti& hfm);

    // Calcule l'aire de drainage, effectué dans le 3e constructeur (utilisé) automatiquement
    void compute(HeightFieldMulti& hfm);
    // Simule la répartition de l'humidité (filtre moyen)
    void spread();
    // Image des aires de drainage
    QImage getImage();
};

#endif // DRAINAGEAREA_H

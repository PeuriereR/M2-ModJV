#ifndef HEIGHTFIELDMULTI_H
#define HEIGHTFIELDMULTI_H

#include "heightfield.h"

// Classe représentant un HeightField multi-couches

class HeightFieldMulti
{
public:

    ScalarField2 bedrock;
    ScalarField2 sediment;
    // water ...

    HeightFieldMulti(){}
    HeightFieldMulti(ScalarField2 bed, ScalarField2 sed);

    // Renvoie le HeightField total
    HeightField getHF();
};

#endif // HEIGHTFIELDMULTI_H

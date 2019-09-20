#ifndef VEGETFIR_H
#define VEGETFIR_H

#include "veget.h"

class VegetFir : public Veget
{
public:
    VegetFir();
    VegetFir(ScalarField2 bed, ScalarField2 sed);
    QImage getImage(QImage image);

    ScalarField2 ProbaExist();
};

#endif // VEGETFIR_H

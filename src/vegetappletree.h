#ifndef VEGETAPPLETREE_H
#define VEGETAPPLETREE_H

#include "veget.h"

class VegetAppleTree : public Veget
{
public:
    VegetAppleTree();
    VegetAppleTree(ScalarField2 bed, ScalarField2 sed);
    void objForest(QString name);

    ScalarField2 ProbaExist();
};

#endif // VEGETAPPLETREE_H

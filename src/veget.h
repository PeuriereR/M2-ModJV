#ifndef VEGET_H
#define VEGET_H
#include "heightfieldmulti.h"
#include "forest.h"
#include "drainagearea.h"
class Veget : public HeightFieldMulti
{
protected:
    DrainageArea da;
public:
    //Constructeurs
    Veget();
    Veget(ScalarField2 bed, ScalarField2 sed);
    //Destructeur
    virtual ~Veget(){}

    //Ensemble des arbres de la végétation
    Forest forest;


    //Génère une grille donnant une probabilité d'exister en chaque point de la taille du terrain
    virtual ScalarField2 ProbaExist();
    //Génère une forêt en tirant nbTree position aléatoire dans le terrain
    void GenForest(int nbTree,DrainageArea da);
    //Dessine sur une image les arbres
    virtual QImage getImage(QImage image);
    //Export l'obj de la forêt
    virtual void objForest(QString name);
    //Effectue nbStep de simulation de la forêt
    void SimulateStep(int nbStep);

};

#endif // VEGET_H

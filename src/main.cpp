#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

#include "analyticfieldridgeattenuate.h"
#include "heightfieldmulti.h"

#include "vegetfir.h"
#include "vegetappletree.h"

#include "thermalerosion.h"
#include "hydroerosion.h"

#include "dijkstra.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Creation du terrain
    AnalyticFieldRidgeAttenuate af(70,250,13,0.49);

    HeightField hf = af.getHeightField(Box2(Vec2(0,0),Vec2(500,500)),500,500);
    HeightFieldMulti hfm(hf,ScalarField2(hf.b2(),hf.nx(),hf.ny()));
    qDebug() << "Fin de génération du terrain";

    // Erosion
    HydroErosion he;
    he.slopeErosion(hfm, 140);
    he.carriage(hfm, 10000);
    ThermalErosion te;
    te.carriage(hfm, 500000);
    qDebug() << "Fin des érosions";

    // Vegetation: Sapin & Buisson
    VegetFir hfm_tree(hfm.getHF(), ScalarField2(hf.b2(),hf.nx(),hf.ny()));
    VegetAppleTree hfm_AppleTree(hfm.getHF(), ScalarField2(hf.b2(),hf.nx(),hf.ny()));

    DrainageArea da(hfm_tree);
    hfm_tree.GenForest(5000,da);
    hfm_AppleTree.GenForest(5000,da);
    qDebug() << "Fin de la création des forêts";

    // Simulation de vieillissement d'écosystemes
    hfm_tree.SimulateStep(100);
    hfm_AppleTree.SimulateStep(100);
    qDebug() << "Fin de simulation de vie des écosystemes";

    // Réseau routier
     QVector<Vec2> spots = hfm_tree.getHF().findCitySpots(150,100);

    std::vector<Veget> forests;
    forests.push_back(hfm_AppleTree);
    forests.push_back(hfm_tree);

    int center = rand() % spots.size();
    Dijkstra di(hfm_tree.getHF(),forests,spots,center);
    qDebug() << "Fin de création du réseau routier";

    // Création du  mesh du terrain
    di.getHF().createAFHRoadColoredMesh("under_tree_path",":/images/data/biome2.png",di.getPath());

    // Création des meshs des arbres
    hfm_AppleTree.forest.pos = di.getForest(0).forest.pos;
    hfm_AppleTree.forest.age = di.getForest(0).forest.age;

    hfm_tree.forest.pos = di.getForest(1).forest.pos;
    hfm_tree.forest.age = di.getForest(1).forest.age;

    hfm_tree.objForest("forest_road.obj");
    hfm_AppleTree.objForest("forest_apple_road.obj");

    qDebug() << "Fin de génération des fichiers obj";

    qDebug() << "END " ;

    return a.exec();
//        return 1;
}



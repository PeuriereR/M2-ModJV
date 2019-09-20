#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H

#include <QFile>

#include "scalarfield2.h"
#include "vec3.h"
#include "perlinnoise.h"

// Classe représentant un champ de hauteurs

#define NO_COLOR 0 // CreateMesh
#define AF_COLOR 1
#define SF_COLOR 2
#define AFROAD_COLOR 3

class HeightField : public ScalarField2
{
    // Fonctions de coloration
    Vec3 biome(float e, float m, float minH, float maxH); // Par biome
    Vec3 perlinBiome(PerlinNoise& pn, QImage& img, Vec3 point, float minH, float maxH); // Par PN
    Vec3 SF2Color(QImage& img, ScalarField2& sf2, Vec3 point, float minV, float maxV); // Par SF2

    // Fonction d'export obj
    void createMesh(QString objName, int mode, QString colorChartName, ScalarField2& sf2,std::vector<Vec2> pos);

    // Critère pour findCitySpots
    float planarSum(Vec2 v, float planarRadius);

public:
    // Constructeurs
    HeightField(){}
    HeightField(Box2 b2, int nx, int ny);
    HeightField(Box2 b2, QImage img);

    // Utilitaire
    float height(Vec2 v);
    float slope(Vec2 v);
    Vec3 normal(Vec2 v);
    ScalarField2 slopeMap();
    // ScalarField2 shadowMap();

    int getLowerNeighbors(Vec2 pos, Vec2 neighbors[8], float diffHeights[8], float& totalDiffHeight);

    // Fonctions d'export obj par fonction de coloration
    void createMesh(QString objName);
    void createAFHColoredMesh(QString objName, QString colorChartName);
    void createSF2ColoredMesh(QString objName, QString colorChartName, ScalarField2& sf2);
    void createAFHRoadColoredMesh(QString objName, QString colorChartName,std::vector<Vec2> pos);

    // Fonction de recherche des lieux plats
    QVector<Vec2> findCitySpots(float minDistance, float radius);

};

#endif // HEIGHTFIELD_H

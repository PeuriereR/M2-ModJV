#ifndef SCALARFIELD2_H
#define SCALARFIELD2_H

#include <QVector>
#include <math.h>
#include <QImage>
#include "grid2.h"

// Classe représentant une grille 2D associée à des valeurs

class ScalarField2 : public Grid2
{
protected:
    // Valeurs du SF2
    QVector<float> values;
public:
    // Constructeurs
    ScalarField2(){}
    ScalarField2(Box2 b2, int nx, int ny);
    ScalarField2(Box2 b2, QImage img);
    ScalarField2(Box2 b2, int nx, int ny,float value);

    inline int index(int i, int j){ return j*_nx+i; }
    Vec2 posFromIndex(int index){return Vec2(index%_nx,index/_nx);}

    // Getters
    float value(int i,int j);
    float value(const Vec2& v);

    // Setters
    void putValue(int i, int j, float value);
    void putValue(const Vec2& v, float value);
    void addValue(int i, int j, float value);
    void addValue(const Vec2& v, float value);

    void clearValues();


    // Utilitaire
    Vec2 gradient(Vec2 v);
    int getSF2Neighbors(int x, int y, int neighbors[16]);
    bool inSF2(int x,int y);
    Vec2 getRandomPos();
    void getRange(float& min, float& max);
    void normalize(float min, float max);

    // Renvoie l'image du SF2
    virtual QImage getImage();

    // Applique une racine sur les valeur
    void racine();
};

#endif // SCALARFIELD2_H

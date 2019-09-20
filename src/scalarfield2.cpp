#include "scalarfield2.h"

ScalarField2::ScalarField2(Box2 b2, int nx, int ny): ScalarField2(b2,nx,ny,0.0){}

ScalarField2::ScalarField2(Box2 b2, int nx, int ny, float value): Grid2(b2,nx,ny){
    values.fill(value,nx*ny);
}

ScalarField2::ScalarField2(Box2 b2, QImage img): ScalarField2(b2, img.width(), img.height()){
    int i, j;
    for (j = 0; j < ny(); ++j) {
        for (i = 0; i < nx(); ++i) {
            int idx = index(i, j);
            values[idx] = img.pixelColor(i, j).blue();
        }
    }
}

float ScalarField2::value(int i,int j){
    return values[index(i,j)];
}

float ScalarField2::value(const Vec2& v){
    return value(v.x(), v.y());
    // Nous n'utilisons pas l'interpolation
}

void ScalarField2::putValue(int i, int j, float value){
    values[index(i,j)]= value;
}

void ScalarField2::putValue(const Vec2& v, float value){
    putValue(v.x(), v.y(), value);
}

void ScalarField2::addValue(int i, int j, float value){
    values[index(i,j)]+= value;
}

void ScalarField2::addValue(const Vec2& v, float value){
    addValue(v.x(), v.y(), value);
}

void ScalarField2::clearValues(){
    values.clear();
}

Vec2 ScalarField2::gradient(Vec2 v){
    int neighbors[8];
    getNeighbors(v,neighbors);

    return Vec2(
                (value(neighbors[2],neighbors[3]) - value(neighbors[6],neighbors[7]))/2,
            (value(neighbors[4],neighbors[5]) - value(neighbors[0],neighbors[1]))/2
            );
}

int ScalarField2::getSF2Neighbors(int x, int y, int neighbors[16]){
    // Renvoie les voisins en x , y

    int compteur = 0;

    for (int var_x = x-1; var_x <= x+1; ++var_x) {
        for (int var_y = y-1; var_y <= y+1; ++var_y) {
            if(var_x==x && var_y==y) continue;

            if( inSF2(var_x,var_y) ){
                neighbors[compteur * 2] = var_x;
                neighbors[compteur * 2 +1] = var_y;
                compteur++;
            }
        }
    }
    return compteur; // nombre de voisin
}

bool ScalarField2::inSF2(int x,int y){
    return (x>=0 && x<nx() && y>=0 && y<ny());
}


Vec2 ScalarField2::getRandomPos(){
    return Vec2(rand()% nx(),rand() % ny());
}

void ScalarField2::getRange(float& min, float& max){
    min = *std::min_element(values.begin(), values.end());
    max = *std::max_element(values.begin(), values.end());
}

void ScalarField2::normalize(float min, float max){
    float range = max - min;

    for (int i = 0; i < values.size(); ++i) {
        values[i] = (values[i] - min)/ range * 255.0;
    }
}

QImage ScalarField2::getImage(){
    float min,max;
    getRange(min, max);
    normalize(min, max);

    QImage image(nx(), ny(), QImage::Format_RGB32);
    for (int x = 0; x < nx(); ++x) {
        for (int y = 0; y < ny(); ++y) {
            image.setPixel(x,y, qRgb(values[index(x,y)],values[index(x,y)],values[index(x,y)]) );
        }
    }
    return image;
}

void ScalarField2::racine(){
    for (int x = 0; x < values.size(); ++x) {
        values[x] = sqrt(values[x]);
    }
}

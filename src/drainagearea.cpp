#include "drainagearea.h"

DrainageArea::DrainageArea(){}

DrainageArea::DrainageArea(Box2 b2, int nx, int ny): ScalarField2(b2,nx,ny,1.0){}

DrainageArea::DrainageArea(HeightFieldMulti& hfm):ScalarField2(hfm.bedrock.b2(), hfm.bedrock.nx(), hfm.bedrock.ny(), 1.0){
    compute(hfm);
}

void DrainageArea::compute(HeightFieldMulti& hfm){

    // On récupère le heightfield
    HeightField heightMap = hfm.getHF();

    // Initialisation de l'aire de drainage
    // Les valeurs sont déjà partout à 1.0

    QVector<Vec2> indexQueue;
    for (int x = 0; x < nx(); ++x) {
        for (int y = 0; y < ny(); ++y) {
            indexQueue.push_back( Vec2(x,y) );
        }
    }

    // Tri par hauteur décroissant
    std::sort(indexQueue.begin(), indexQueue.end(), [&](Vec2 a, Vec2 b){
        return heightMap.height(a) > heightMap.height(b);
    });

    // On déverse sur un voisin

    Vec2 neighbors[8];
    int nbNeighbors;
    float diffHeights[8];
    float totalDiffHeight;

    Vec2 position; // Position actuelle

    for (int i = 0; i < indexQueue.size(); ++i) {
        // On récupère une position
        position = indexQueue[i];
        // Et ses voisins plus bas
        nbNeighbors = heightMap.getLowerNeighbors(position, neighbors, diffHeights, totalDiffHeight);
        if(nbNeighbors == 0) continue; // pas de vosins plus bas, fin de l'expansion

        // On calcule les pourcentages en fonction des distances
        for (int neighbor = 0; neighbor < nbNeighbors; ++neighbor) {
            diffHeights[neighbor] /= totalDiffHeight;
        }

        float currentDrainageVal = value(position);

        for (int neighbor = 0; neighbor < nbNeighbors; ++neighbor) {
            // Quantité proportionnelle à la différence de hauteur à deverser
            float qty = diffHeights[neighbor] * currentDrainageVal;
            // On déverse
            addValue( neighbors[neighbor], qty);
        }
    }
}


void DrainageArea::spread(){
    int neighb[16];
    int nb;

    // Filtre moyen appliqué sur le ScalarField2
    for (int var_x = 0; var_x < nx(); ++var_x) {
        for (int var_y = 0; var_y < ny(); ++var_y) {

            nb = getSF2Neighbors(var_x,var_y,neighb);
            if (nb==0) continue;

            float currentValue = value(var_x,var_y);

            float total = 0;
            for (int val = 0; val < nb; ++val) {
                total += value( neighb[val*2], neighb[val*2+1] );
            }

            total+=currentValue;
            putValue(var_x,var_y, (total/(nb+1)) );
        }
    }

}

QImage DrainageArea::getImage(){
    racine(); // Pour rendre les données visibles
    racine();

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

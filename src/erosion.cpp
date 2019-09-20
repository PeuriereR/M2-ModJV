#include "erosion.h"

Erosion::Erosion(){}

void Erosion::slopeErosion(HeightFieldMulti& hfm, float maxHeight){
    // bed_ij = -e * g(s(p_ij)) s slope g transfert

    float erosionQty = 0;
    ScalarField2 slopemap = hfm.getHF().slopeMap();

    for (int x = 0; x < hfm.sediment.nx(); ++x) {
        for (int y = 0; y < hfm.sediment.ny(); ++y) {

            // Application de notre fonction d'érosion
            erosionQty =  3 +  10 * transfer(slopemap.value(x,y), maxHeight);
            // On ajoute les sédiments
            hfm.sediment.putValue(x,y, erosionQty);
            // On érode le bedrock
            hfm.bedrock.addValue(x,y, - erosionQty);
        }
    }
}


void Erosion::globalErosion(HeightFieldMulti& hfm, float factor){
    hfm.sediment = ScalarField2( hfm.sediment.b2(), hfm.sediment.nx(), hfm.sediment.ny(), factor);
    // Supprimer du bedrock ici de changera rien
}

float Erosion::transfer(float value, float maxHeight){
    // Fonction extraite du code de E.Galin (Blob shadertoy)

    float x = std::min(std::max(value,0.f),1.f);
    float y = (1.0- (x*x) );
    float val = y*y*y * ( 0.01 * maxHeight );
    return val;
}


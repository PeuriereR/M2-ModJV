#include "heightfieldmulti.h"

HeightFieldMulti::HeightFieldMulti(ScalarField2 bed, ScalarField2 sed): bedrock(bed), sediment(sed){}

HeightField HeightFieldMulti::getHF(){
    HeightField hf(bedrock.b2(),bedrock.nx(),bedrock.ny());

    for(int i=0; i<bedrock.nx(); i++){
        for(int j=0; j<bedrock.ny(); j++){
            // Fais les somme des différentes couches
            hf.putValue(i,j,bedrock.value(i,j));
            hf.addValue(i,j,sediment.value(i,j));
        }
    }

    return hf;
}


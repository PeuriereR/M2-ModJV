#include "vegetfir.h"
VegetFir::VegetFir()
{

}


VegetFir::VegetFir(ScalarField2 bed, ScalarField2 sed): Veget(bed,sed){}

ScalarField2 VegetFir::ProbaExist() {
    ScalarField2 sf2(bedrock.b2(),bedrock.nx(),bedrock.ny(),1.);
    HeightField hf = getHF();
    ScalarField2 slopeMap = hf.slopeMap();
    float maxHeight, minHeight,maxSlope,minSlope;
    hf.getRange(minHeight,maxHeight);
    slopeMap.getRange(minSlope,maxSlope);
    da.spread();
    da.spread();
    da.getImage().save("drainagetest.png","PNG");

    for(int i = 0; i < sf2.nx(); i++){
        for(int j = 0; j < sf2.ny();j++){

            float height = abs(minHeight) + hf.height(Vec2(i,j));
            float probaH = height / (maxHeight + abs(minHeight));

            if(probaH < 0.3){
                probaH = 0;
            }

            probaH = probaH * probaH;


            float slope = abs(minSlope) + slopeMap.value(i,j);
            float probaSlope = slope / (maxSlope + minSlope);
            //ajout proba da


            sf2.putValue(i,j,probaH * probaSlope);
        }
    }
    return sf2;
}

QImage VegetFir::getImage(QImage image){

    QColor color(120,120,0);

    for(unsigned int i = 0; i < forest.pos.size();i++)
    {
        image.setPixel(forest.pos[i].x(),forest.pos[i].y(), color.rgb());
        for(float j = 1; j - 1 < (forest.GetRadius(i)); j++){
            image.setPixel(forest.pos[i].x() - j,forest.pos[i].y(), color.rgb());

            image.setPixel(forest.pos[i].x() - j,forest.pos[i].y() - j, color.rgb());


            image.setPixel(forest.pos[i].x() + j,forest.pos[i].y() - j,color.rgb());


            image.setPixel(forest.pos[i].x() - j,forest.pos[i].y() + j, color.rgb());

            image.setPixel(forest.pos[i].x() + j,forest.pos[i].y() + j, color.rgb());

            image.setPixel(forest.pos[i].x(),forest.pos[i].y() - j, color.rgb());

            image.setPixel(forest.pos[i].x() + j,forest.pos[i].y(), color.rgb());

            image.setPixel(forest.pos[i].x(),forest.pos[i].y() + j, color.rgb());
        }
    }
    return image;

}

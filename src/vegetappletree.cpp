#include "vegetappletree.h"
#include <QDebug>

VegetAppleTree::VegetAppleTree()
{

}


VegetAppleTree::VegetAppleTree(ScalarField2 bed, ScalarField2 sed): Veget(bed,sed){}

ScalarField2 VegetAppleTree::ProbaExist() {
    ScalarField2 sf2(bedrock.b2(),bedrock.nx(),bedrock.ny(),1.);
    HeightField hf = getHF();
    ScalarField2 slopeMap = hf.slopeMap();
    float maxHeight, minHeight,maxSlope,minSlope,maxDA,minDA;
    hf.getRange(minHeight,maxHeight);
    slopeMap.getRange(minSlope,maxSlope);
    da.getRange(minDA,maxDA);
    for(int i = 0; i < 50;i++)
        da.spread();
    da.getImage().save("drainagetest.png","PNG");

    for(int i = 0; i < sf2.nx(); i++){
        for(int j = 0; j < sf2.ny();j++){

            float height =  abs(minHeight) + hf.height(Vec2(i,j));
            float probaH =  height / (maxHeight + abs(minHeight));

            if(probaH < 0.2 || probaH > 0.45){
                probaH = 0;
            }else{
                probaH -= 0.25;
                probaH = (1.0 - probaH*probaH);
                probaH = probaH * probaH * probaH;
            }

            float probaDA  = da.value(i,j) / (maxDA/5);
            if(probaDA > 1)
                probaDA = 1.;
            sf2.putValue(i,j, probaH * sqrt(probaDA));
        }
    }



    return sf2;

}

void VegetAppleTree::objForest(QString name){

    QString color = " 50 170 50 ";

    HeightField hf = getHF();
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed to create forest.obj ";
        return;
    }

    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    for(unsigned int i = 0; i < forest.pos.size(); i++){

        float size = (forest.GetRadius(i) * 3) + 2;
        float h = hf.value(forest.pos[i].x(),forest.pos[i].y());

        flux << "v " << forest.pos[i].x() + size * 0.000000  << " " << h + size * 0.500000 << " " << forest.pos[i].y() + size * -0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.250000  << " " << h + size * 0.433000 << " " << forest.pos[i].y() + size * -0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.433000  << " " << h + size * 0.250000 << " " << forest.pos[i].y() + size * -0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.500000  << " " << h + size * 0.000000 << " " << forest.pos[i].y() + size * 0.000000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.433000  << " " << h + size * -0.25000 << " " << forest.pos[i].y() + size * 0.000000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.250000  << " " << h + size * -0.43300 << " " << forest.pos[i].y() + size * 0.000000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.000000  << " " << h + size * -0.50000 << " " << forest.pos[i].y() + size * 0.000000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.125000  << " " << h + size * 0.433000 << " " << forest.pos[i].y() + size * 0.216500 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.216500  << " " << h + size * 0.250000 << " " << forest.pos[i].y() + size * 0.375000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.250000  << " " << h + size * 0.000000 << " " << forest.pos[i].y() + size * 0.433000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.216500  << " " << h + size * -0.25000 << " " << forest.pos[i].y() + size * 0.375000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.125000  << " " << h + size * -0.43300 << " " << forest.pos[i].y() + size * 0.216500 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.125000 << " " << h + size *  0.43300 << " " << forest.pos[i].y() + size * 0.216500 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.216500 << " " << h + size *  0.25000 << " " << forest.pos[i].y() + size * 0.375000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.250000 << " " << h + size *  0.00000 << " " << forest.pos[i].y() + size * 0.433000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.216500 << " " << h + size *  -0.2500 << " " << forest.pos[i].y() + size *  0.375000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.125000 << " " << h + size *  -0.4330 << " " << forest.pos[i].y() + size *  0.216500 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.250000 << " " << h + size *  0.43300 << " " << forest.pos[i].y() + size * -0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.433000 << " " << h + size *  0.25000 << " " << forest.pos[i].y() + size * -0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.500000 << " " << h + size *  0.00000 << " " << forest.pos[i].y() + size * 0.000000 <<  color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.433000 << " " << h + size *  -0.2500 << " " << forest.pos[i].y() + size *  0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.250000 << " " << h + size *  -0.4330 << " " << forest.pos[i].y() + size *  0.000000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.125000 << " " << h + size *  0.43300 << " " << forest.pos[i].y() + size * -0.216500 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.216500 << " " << h + size *  0.25000 << " " << forest.pos[i].y() + size * -0.375000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.250000 << " " << h + size *  -0.0000 << " " << forest.pos[i].y() + size *  -0.43300 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.216500 << " " << h + size *  -0.2500 << " " << forest.pos[i].y() + size *  -0.37500 << color << endl;
        flux << "v " << forest.pos[i].x() + size * -0.125000 << " " << h + size *  -0.4330 << " " << forest.pos[i].y() + size *  -0.21650 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.125000  << " " << h + size * 0.433000 << " " << forest.pos[i].y() + size * -0.216500 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.216500  << " " << h + size * 0.250000 << " " << forest.pos[i].y() + size * -0.375000 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.250000  << " " << h + size * -0.00000 << " " << forest.pos[i].y() + size *  -0.43300 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.216500  << " " << h + size * -0.25000 << " " << forest.pos[i].y() + size *  -0.37500 << color << endl;
        flux << "v " << forest.pos[i].x() + size * 0.125000  << " " << h + size * -0.43300 << " " << forest.pos[i].y() + size *  -0.21650 << color << endl;
    }
    flux << "vn 0.000000 1.000000 0.000000" << endl;
    flux << "vn 0.279200 0.829500 0.483700" << endl;
    flux << "vn 0.558500 0.829500 0.000000" << endl;
    flux << "vn 0.442100 0.467100 0.765700" << endl;
    flux << "vn 0.884200 0.467100 0.000000" << endl;
    flux << "vn 0.500000 0.000000 0.866000" << endl;
    flux << "vn 1.000000 0.000000 0.000000" << endl;
    flux << "vn 0.442100 -0.467100 0.765700" << endl;
    flux << "vn 0.884200 -0.467100 0.000000" << endl;
    flux << "vn 0.279300 -0.829500 0.483700" << endl;
    flux << "vn 0.558500 -0.829500 0.000000" << endl;
    flux << "vn 0.000000 -1.000000 0.000000" << endl;
    flux << "vn -0.279300 0.829500 0.483700" << endl;
    flux << "vn -0.442100 0.467100 0.765700" << endl;
    flux << "vn -0.500000 0.000000 0.866000" << endl;
    flux << "vn -0.442100 -0.467100 0.765700" << endl;
    flux << "vn -0.279200 -0.829500 0.483700" << endl;
    flux << "vn -0.558500 0.829500 0.000000" << endl;
    flux << "vn -0.884200 0.467100 0.000000" << endl;
    flux << "vn -1.000000 0.000000 0.000000" << endl;
    flux << "vn -0.884200 -0.467100 0.000000" << endl;
    flux << "vn -0.558500 -0.829500 0.000000" << endl;
    flux << "vn -0.279200 0.829500 -0.483700" << endl;
    flux << "vn -0.442100 0.467100 -0.765700" << endl;
    flux << "vn -0.500000 0.000000 -0.866000" << endl;
    flux << "vn -0.442100 -0.467100 -0.765700" << endl;
    flux << "vn -0.279300 -0.829500 -0.483700" << endl;
    flux << "vn 0.279300 0.829500 -0.483700" << endl;
    flux << "vn 0.442100 0.467100 -0.765700"  << endl;
    flux << "vn 0.500000 0.000000 -0.866000" << endl;
    flux << "vn 0.442100 -0.467100 -0.765700" << endl;
    flux << "vn 0.279200 -0.829500 -0.483700" << endl;
    for(unsigned int i = 0; i < forest.pos.size(); i++){
         flux << "f " << i * 32 + 2  <<  "//" << i*32 + 3  << " " << i * 32 + 8  <<  "//" << i * 32 + 2  << " " <<   i * 32 + 9  <<  "//" << i * 32 + 4 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 8  <<  "//" << i * 32 + 2  << " " <<   i * 32 + 2  <<  "//" << i * 32 + 3 << endl;
         flux << "f " << i * 32 + 2  <<  "//" << i*32 + 3  << " " << i * 32 + 9  <<  "//" << i * 32 + 4  << " " <<   i * 32 + 3  <<  "//" << i * 32 + 5 << endl;
         flux << "f " << i * 32 + 3  <<  "//" << i*32 + 5  << " " << i * 32 + 9  <<  "//" << i * 32 + 4  << " " <<   i * 32 + 10 <<  "//" << i * 32 + 6<< endl;
         flux << "f " << i * 32 + 3  <<  "//" << i*32 + 5  << " " << i * 32 + 10 <<  "//" << i * 32 + 6  << " " <<   i * 32 + 4  <<  "//" << i * 32 + 7 << endl;
         flux << "f " << i * 32 + 4  <<  "//" << i*32 + 7  << " " << i * 32 + 10 <<  "//" << i * 32 + 6  << " " <<   i * 32 + 11 <<  "//" << i * 32 + 8 << endl;
         flux << "f " << i * 32 + 4  <<  "//" << i*32 + 7  << " " << i * 32 + 11 <<  "//" << i * 32 + 8  << " " <<   i * 32 + 5  <<  "//" << i * 32 + 9 << endl;
         flux << "f " << i * 32 + 5  <<  "//" << i*32 + 9  << " " << i * 32 + 11 <<  "//" << i * 32 + 8  << " " <<   i * 32 + 12 <<  "//" << i * 32 + 10 << endl;
         flux << "f " << i * 32 + 5  <<  "//" << i*32 + 9  << " " << i * 32 + 12 <<  "//" << i * 32 + 10 << " " <<   i * 32 + 6  <<  "//" << i * 32 + 11 << endl;
         flux << "f " << i * 32 + 6  <<  "//" << i*32 + 11 << " " << i * 32 + 12 <<  "//" << i * 32 + 10 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 13 <<  "//" << i * 32 + 13 << " " <<   i * 32 + 8  <<  "//" << i * 32 + 2 << endl;
         flux << "f " << i * 32 + 8  <<  "//" << i*32 + 2  << " " << i * 32 + 13 <<  "//" << i * 32 + 13 << " " <<   i * 32 + 14 <<  "//" << i * 32 + 14 << endl;
         flux << "f " << i * 32 + 8  <<  "//" << i*32 + 2  << " " << i * 32 + 14 <<  "//" << i * 32 + 14 << " " <<   i * 32 + 9  <<  "//" << i * 32 + 4 << endl;
         flux << "f " << i * 32 + 9  <<  "//" << i*32 + 4  << " " << i * 32 + 14 <<  "//" << i * 32 + 14 << " " <<   i * 32 + 15 <<  "//" << i * 32 + 15 << endl;
         flux << "f " << i * 32 + 9  <<  "//" << i*32 + 4  << " " << i * 32 + 15 <<  "//" << i * 32 + 15 << " " <<   i * 32 + 10 <<  "//" << i * 32 + 6 << endl;
         flux << "f " << i * 32 + 10 <<  "//" << i*32 + 6  << " " << i * 32 + 15 <<  "//" << i * 32 + 15 << " " <<   i * 32 + 16 <<  "//" << i * 32 + 16 << endl;
         flux << "f " << i * 32 + 10 <<  "//" << i*32 + 6  << " " << i * 32 + 16 <<  "//" << i * 32 + 16 << " " <<   i * 32 + 11 <<  "//" << i * 32 + 8 << endl;
         flux << "f " << i * 32 + 11 <<  "//" << i*32 + 8  << " " << i * 32 + 16 <<  "//" << i * 32 + 16 << " " <<   i * 32 + 17 <<  "//" << i * 32 + 17 << endl;
         flux << "f " << i * 32 + 11 <<  "//" << i*32 + 8  << " " << i * 32 + 17 <<  "//" << i * 32 + 17 << " " <<   i * 32 + 12 <<  "//" << i * 32 + 10 << endl;
         flux << "f " << i * 32 + 12 <<  "//" << i*32 + 10 << " " << i * 32 + 17 <<  "//" << i * 32 + 17 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 18 <<  "//" << i * 32 + 18 << " " <<   i * 32 + 13 <<  "//" << i * 32 + 13 << endl;
         flux << "f " << i * 32 + 13 <<  "//" << i*32 + 13 << " " << i * 32 + 18 <<  "//" << i * 32 + 18 << " " <<   i * 32 + 19 <<  "//" << i * 32 + 19 << endl;
         flux << "f " << i * 32 + 13 <<  "//" << i*32 + 13 << " " << i * 32 + 19 <<  "//" << i * 32 + 19 << " " <<   i * 32 + 14 <<  "//" << i * 32 + 14 << endl;
         flux << "f " << i * 32 + 14 <<  "//" << i*32 + 14 << " " << i * 32 + 19 <<  "//" << i * 32 + 19 << " " <<   i * 32 + 20 <<  "//" << i * 32 + 20 << endl;
         flux << "f " << i * 32 + 14 <<  "//" << i*32 + 14 << " " << i * 32 + 20 <<  "//" << i * 32 + 20 << " " <<   i * 32 + 15 <<  "//" << i * 32 + 15 << endl;
         flux << "f " << i * 32 + 15 <<  "//" << i*32 + 15 << " " << i * 32 + 20 <<  "//" << i * 32 + 20 << " " <<   i * 32 + 21 <<  "//" << i * 32 + 21 << endl;
         flux << "f " << i * 32 + 15 <<  "//" << i*32 + 15 << " " << i * 32 + 21 <<  "//" << i * 32 + 21 << " " <<   i * 32 + 16 <<  "//" << i * 32 + 16 << endl;
         flux << "f " << i * 32 + 16 <<  "//" << i*32 + 16 << " " << i * 32 + 21 <<  "//" << i * 32 + 21 << " " <<   i * 32 + 22 <<  "//" << i * 32 + 22 << endl;
         flux << "f " << i * 32 + 16 <<  "//" << i*32 + 16 << " " << i * 32 + 22 <<  "//" << i * 32 + 22 << " " <<   i * 32 + 17 <<  "//" << i * 32 + 17 << endl;
         flux << "f " << i * 32 + 17 <<  "//" << i*32 + 17 << " " << i * 32 + 22 <<  "//" << i * 32 + 22 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 23 <<  "//" << i * 32 + 23 << " " <<   i * 32 + 18 <<  "//" << i * 32 + 18 << endl;
         flux << "f " << i * 32 + 18 <<  "//" << i*32 + 18 << " " << i * 32 + 23 <<  "//" << i * 32 + 23 << " " <<   i * 32 + 24 <<  "//" << i * 32 + 24 << endl;
         flux << "f " << i * 32 + 18 <<  "//" << i*32 + 18 << " " << i * 32 + 24 <<  "//" << i * 32 + 24 << " " <<   i * 32 + 19 <<  "//" << i * 32 + 19 << endl;
         flux << "f " << i * 32 + 19 <<  "//" << i*32 + 19 << " " << i * 32 + 24 <<  "//" << i * 32 + 24 << " " <<   i * 32 + 25 <<  "//" << i * 32 + 25 << endl;
         flux << "f " << i * 32 + 19 <<  "//" << i*32 + 19 << " " << i * 32 + 25 <<  "//" << i * 32 + 25 << " " <<   i * 32 + 20 <<  "//" << i * 32 + 20 << endl;
         flux << "f " << i * 32 + 20 <<  "//" << i*32 + 20 << " " << i * 32 + 25 <<  "//" << i * 32 + 25 << " " <<   i * 32 + 26 <<  "//" << i * 32 + 26 << endl;
         flux << "f " << i * 32 + 20 <<  "//" << i*32 + 20 << " " << i * 32 + 26 <<  "//" << i * 32 + 26 << " " <<   i * 32 + 21 <<  "//" << i * 32 + 21 << endl;
         flux << "f " << i * 32 + 21 <<  "//" << i*32 + 21 << " " << i * 32 + 26 <<  "//" << i * 32 + 26 << " " <<   i * 32 + 27 <<  "//" << i * 32 + 27 << endl;
         flux << "f " << i * 32 + 21 <<  "//" << i*32 + 21 << " " << i * 32 + 27 <<  "//" << i * 32 + 27 << " " <<   i * 32 + 22 <<  "//" << i * 32 + 22 << endl;
         flux << "f " << i * 32 + 22 <<  "//" << i*32 + 22 << " " << i * 32 + 27 <<  "//" << i * 32 + 27 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 28 <<  "//" << i * 32 + 28 << " " <<   i * 32 + 23 <<  "//" << i * 32 + 23 << endl;
         flux << "f " << i * 32 + 23 <<  "//" << i*32 + 23 << " " << i * 32 + 28 <<  "//" << i * 32 + 28 << " " <<   i * 32 + 29 <<  "//" << i * 32 + 29 << endl;
         flux << "f " << i * 32 + 23 <<  "//" << i*32 + 23 << " " << i * 32 + 29 <<  "//" << i * 32 + 29 << " " <<   i * 32 + 24 <<  "//" << i * 32 + 24 << endl;
         flux << "f " << i * 32 + 24 <<  "//" << i*32 + 24 << " " << i * 32 + 29 <<  "//" << i * 32 + 29 << " " <<   i * 32 + 30 <<  "//" << i * 32 + 30 << endl;
         flux << "f " << i * 32 + 24 <<  "//" << i*32 + 24 << " " << i * 32 + 30 <<  "//" << i * 32 + 30 << " " <<   i * 32 + 25 <<  "//" << i * 32 + 25 << endl;
         flux << "f " << i * 32 + 25 <<  "//" << i*32 + 25 << " " << i * 32 + 30 <<  "//" << i * 32 + 30 << " " <<   i * 32 + 31 <<  "//" << i * 32 + 31 << endl;
         flux << "f " << i * 32 + 25 <<  "//" << i*32 + 25 << " " << i * 32 + 31 <<  "//" << i * 32 + 31 << " " <<   i * 32 + 26 <<  "//" << i * 32 + 26 << endl;
         flux << "f " << i * 32 + 26 <<  "//" << i*32 + 26 << " " << i * 32 + 31 <<  "//" << i * 32 + 31 << " " <<   i * 32 + 32 <<  "//" << i * 32 + 32 << endl;
         flux << "f " << i * 32 + 26 <<  "//" << i*32 + 26 << " " << i * 32 + 32 <<  "//" << i * 32 + 32 << " " <<   i * 32 + 27 <<  "//" << i * 32 + 27 << endl;
         flux << "f " << i * 32 + 27 <<  "//" << i*32 + 27 << " " << i * 32 + 32 <<  "//" << i * 32 + 32 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
         flux << "f " << i * 32 + 1  <<  "//" << i*32 + 1  << " " << i * 32 + 2  <<  "//" << i * 32 + 3  << " " <<   i * 32 + 28 <<  "//" << i * 32 + 28 << endl;
         flux << "f " << i * 32 + 28 <<  "//" << i*32 + 28 << " " << i * 32 + 2  <<  "//" << i * 32 + 3  << " " <<   i * 32 + 3  <<  "//" << i * 32 + 5  << endl;
         flux << "f " << i * 32 + 28 <<  "//" << i*32 + 28 << " " << i * 32 + 3  <<  "//" << i * 32 + 5  << " " <<   i * 32 + 29 <<  "//" << i * 32 + 29 << endl;
         flux << "f " << i * 32 + 29 <<  "//" << i*32 + 29 << " " << i * 32 + 3  <<  "//" << i * 32 + 5  << " " <<   i * 32 + 4  <<  "//" << i * 32 + 7  << endl;
         flux << "f " << i * 32 + 29 <<  "//" << i*32 + 29 << " " << i * 32 + 4  <<  "//" << i * 32 + 7  << " " <<   i * 32 + 30 <<  "//" << i * 32 + 30 << endl;
         flux << "f " << i * 32 + 30 <<  "//" << i*32 + 30 << " " << i * 32 + 4  <<  "//" << i * 32 + 7  << " " <<   i * 32 + 5  <<  "//" << i * 32 + 9  << endl;
         flux << "f " << i * 32 + 30 <<  "//" << i*32 + 30 << " " << i * 32 + 5  <<  "//" << i * 32 + 9  << " " <<   i * 32 + 31 <<  "//" << i * 32 + 31 << endl;
         flux << "f " << i * 32 + 31 <<  "//" << i*32 + 31 << " " << i * 32 + 5  <<  "//" << i * 32 + 9  << " " <<   i * 32 + 6  <<  "//" << i * 32 + 11 << endl;
         flux << "f " << i * 32 + 31 <<  "//" << i*32 + 31 << " " << i * 32 + 6  <<  "//" << i * 32 + 11 << " " <<   i * 32 + 32 <<  "//" << i * 32 + 32 << endl;
         flux << "f " << i * 32 + 32 <<  "//" << i*32 + 32 << " " << i * 32 + 6  <<  "//" << i * 32 + 11 << " " <<   i * 32 + 7  <<  "//" << i * 32 + 12 << endl;
     }
}


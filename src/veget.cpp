#include "veget.h"
#include <QDebug>

Veget::Veget()
{

}


Veget::Veget(ScalarField2 bed, ScalarField2 sed): HeightFieldMulti(bed,sed){}


ScalarField2 Veget::ProbaExist() {
    return ScalarField2(bedrock.b2(),bedrock.nx(),bedrock.ny(),1.0);
}

void Veget::SimulateStep(int nbStep){
    for(int i = 0; i < nbStep ; i++){
        // qDebug() << "Simulation année" << i ;
        forest.Step();
    }
}




void Veget::GenForest(int nbTree,DrainageArea da) {
    this->da = da;
    ScalarField2 sf2_prob = ProbaExist();
    forest.SetLimite(Vec2(bedrock.nx(),bedrock.ny()));
    srand(time(0));
    for(int i = 0; i < nbTree; i++){
        Vec2 rand_pos = sf2_prob.getRandomPos();
        float rand_prob = (rand()) / (float)(RAND_MAX);
        float value = sf2_prob.value(rand_pos.x(),rand_pos.y());
        if(rand_prob < value){
            forest.pos.push_back(rand_pos);
            forest.age.push_back(1);
        }
    }
}



QImage Veget::getImage(QImage image){

    HeightField hf = getHF();
    for(unsigned int i = 0; i < forest.pos.size();i++)
    {
        image.setPixel(forest.pos[i].x(),forest.pos[i].y(), qRgb(25,120,25));
        for(int j = forest.pos[i].x() - forest.GetRadius(i); j < forest.pos[i].x() + (forest.GetRadius(i)); j++){
            for(int k = forest.pos[i].y() - forest.GetRadius(i); k < forest.pos[i].y() + (forest.GetRadius(i)); k++){
                image.setPixel(j,k, qRgb(0,200,0));
            }
       }
    }
    return image;
}


void Veget::objForest(QString name){

    QString color = " 150 190 70 ";

    HeightField hf = getHF();
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed to create forest.obj ";
        return;
    }

    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    for(unsigned int i = 0; i < forest.pos.size(); i++){

        float size = (forest.GetRadius(i)) + 2;
        float h = hf.value(forest.pos[i].x(),forest.pos[i].y());
        flux << "v " << forest.pos[i].x() << " " << h << " " << forest.pos[i].y() - (1*size)                           << color << endl;
        flux << "v " << (size*0.951057) + forest.pos[i].x() << " " << h  << " " << forest.pos[i].y() - (size*0.309017) << color << endl;
        flux << "v " <<  (size*0.587785) +forest.pos[i].x() << " " << h  << " " << forest.pos[i].y() + (size*0.809017) << color << endl;
        flux << "v " << forest.pos[i].x() << " " << h + (2 * size) << " " << forest.pos[i].y()                         << color << endl;
        flux << "v " <<  forest.pos[i].x() - (size*0.587785)  << " " << h << " " << forest.pos[i].y() +(size*0.809017) << color << endl;
        flux << "v " << forest.pos[i].x() - (size*0.951057) << " " << h << " " << forest.pos[i].y() - (size*0.309017)  << color << endl;

        h += (2*size)/3;
        flux << "v " << forest.pos[i].x() << " " << h << " " << forest.pos[i].y() - (1*size)                           << color << endl;
        flux << "v " << (size*0.951057) + forest.pos[i].x() << " " << h << " " << forest.pos[i].y() - (size*0.309017)  << color << endl;
        flux << "v " <<  (size*0.587785) +forest.pos[i].x() << " " << h  << " " << forest.pos[i].y() + (size*0.809017) << color << endl;
        flux << "v " << forest.pos[i].x() << " " << h + 2 * size << " " << forest.pos[i].y()                           << color << endl;
        flux << "v " <<  forest.pos[i].x() - (size*0.587785)  << " " << h << " " << forest.pos[i].y() +(size*0.809017) << color << endl;
        flux << "v " << forest.pos[i].x() - (size*0.951057) << " " << h  << " " << forest.pos[i].y() - (size*0.309017) << color << endl;
    }

    flux << "vn 0.5449 0.3750 -0.7500" << endl;
    flux << "vn 0.8817 0.3750 0.2865" << endl;
    flux << "vn -0.0000 0.3750 0.9270" << endl;
    flux << "vn -0.8817 0.3750 0.2865" << endl;
    flux << "vn -0.5449 0.3750 -0.7500" << endl;
    flux << "vn 0.0000 -1.0000 0.0000" << endl;
    flux << endl;
    for(unsigned int i = 0; i < forest.pos.size(); i++){

        flux << "f " << i*12+1 << "//" << i*12+1 << " " << i*12+4 << "//" << i*12+1<< " " << i*12+2 << "//" << i*12+1 << endl;
        flux << "f " << i*12+2 << "//" << i*12+2 << " " << i*12+4 << "//" << i*12+2<< " " << i*12+3 << "//" << i*12+1 << endl;
        flux << "f " << i*12+3 << "//" << i*12+3 << " " << i*12+4 << "//" << i*12+3<< " " << i*12+5 << "//" << i*12+3 << endl;
        flux << "f " << i*12+5 << "//" << i*12+4 << " " << i*12+4 << "//" << i*12+4<< " " << i*12+6 << "//" << i*12+4 << endl;
        flux << "f " << i*12+6 << "//" << i*12+5 << " " << i*12+4 << "//" << i*12+5<< " " << i*12+1 << "//" << i*12+5 << endl;
        flux << "f " << i*12+1 << "//" << i*12+6 << " " << i*12+2 << "//" << i*12+6<< " " << i*12+3 << "//" << i*12+6 << " " << i*12+5 << "//" << i*12+6 << " " << i*12+6 << "//" << i*12+6 << endl;


        flux << "f " << i*12 + 6+1 << "//" << i*12 + 6+1 << " " << i*12 + 6+4 << "//" << i*12 + 6+1<< " " << i*12 + 6+2 << "//" << i*12 + 6+1 << endl;
        flux << "f " << i*12 + 6+2 << "//" << i*12 + 6+2 << " " << i*12 + 6+4 << "//" << i*12 + 6+2<< " " << i*12 + 6+3 << "//" << i*12 + 6+1 << endl;
        flux << "f " << i*12 + 6+3 << "//" << i*12 + 6+3 << " " << i*12 + 6+4 << "//" << i*12 + 6+3<< " " << i*12 + 6+5 << "//" << i*12 + 6+3 << endl;
        flux << "f " << i*12 + 6+5 << "//" << i*12 + 6+4 << " " << i*12 + 6+4 << "//" << i*12 + 6+4<< " " << i*12 + 6+6 << "//" << i*12 + 6+4 << endl;
        flux << "f " << i*12 + 6+6 << "//" << i*12 + 6+5 << " " << i*12 + 6+4 << "//" << i*12 + 6+5<< " " << i*12 + 6+1 << "//" << i*12 + 6+5 << endl;
        flux << "f " << i*12 + 6+1 << "//" << i*12 + 6+6 << " " << i*12 + 6+2 << "//" << i*12 + 6+6<< " " << i*12 + 6+3 << "//" << i*12 + 6+6 << " " << i*12 + 6+5 << "//" << i*12 + 6+6 << " " << i*12 + 6+6 << "//" << i*12 + 6+6 << endl;

    }
}

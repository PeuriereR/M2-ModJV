#include "forest.h"

Forest::Forest()
{

}


float Forest::GetRadius(int tree){
    return (float)age[tree] / 10.;
}


void Forest::SetLimite(Vec2 limite){
    lim = limite;
}

void Forest::SelfClear(){

    for(unsigned int i = 0; i < pos.size() - 1 ; i++)
    {
        for(unsigned  int j = i + 1; j < pos.size();j++){
            Vec2 rayon = Vec2(pos[i].x() - pos[j].x(),pos[i].y() - pos[j].y());
            if(rayon.length() < GetRadius(i))
            {
                pos.erase(pos.begin()+j);
                age.erase(age.begin()+j);

                j--;
            }
        }
    }
}


float Forest::RandomSeed(int tree){
    float radius = GetRadius(tree);

    float maxRadius = radius * 20;
    return (rand()) / (float)(RAND_MAX / (maxRadius - radius)) + radius;
}

float Forest::probaDeath(int age){

    float proba = (age / 50.) * (age / 50.);

    return proba > 0.6 ? 0.6 : proba;
}

void Forest::Step(){
    std::vector<Vec2> toAdd;
    for(unsigned int i = 0; i < age.size(); i++){

        float rand_procreation = (rand()) / (float)(RAND_MAX);

        if(rand_procreation < 0.07){
            float radius = RandomSeed(i);
            float x = (rand() / (float) (RAND_MAX / radius )) * 2 - radius;
            float y = sqrt(radius*radius - x*x);
            if(rand_procreation < 0.035) //y positif
                toAdd.push_back(Vec2(ceil(pos[i].x()+x),ceil(pos[i].y()+y)));
            else
                toAdd.push_back(Vec2(ceil(pos[i].x()+x),floor(pos[i].y()-y)));
        }


        float rand_prob = (rand()) / (float)(RAND_MAX);
        if(rand_prob < probaDeath(age[i]))
        {
            pos.erase(pos.begin()+i);
            age.erase(age.begin()+i);
            i--;
        }
        else{
        age[i]++;
        }
    }
    for(unsigned int i = 0 ; i < toAdd.size(); i++){
        if(toAdd[i].x() > 0 && toAdd[i].x() < lim.x() && toAdd[i].y() > 0 && toAdd[i].y() < lim.y() ){
            pos.push_back(toAdd[i]);
            age.push_back(1);
        }
    }

    SelfClear();
}

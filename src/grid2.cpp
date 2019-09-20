#include "grid2.h"

Grid2::Grid2(Box2 b2, int nx, int ny): _b2(b2), _nx(nx), _ny(ny){}

Vec2 Grid2::point(const int &i, const int &j)const{
    Vec2 diago = unitDiagonal();
    diago.scale(i,j); // changer le scale
    return _b2.pmin() + diago;
}

int Grid2::nx() const{
    return _nx;
}
int Grid2::ny() const{
    return _ny;
}

Box2& Grid2::b2(){
    return _b2;
}

Vec2 Grid2::unitDiagonal() const{
    return Vec2((_b2.pmax().x()-_b2.pmin().x())/(_nx),(_b2.pmax().y()-_b2.pmin().y())/(_ny));
}

void Grid2::getNeighbors(Vec2 v, int neighbors[8]){
    int i = v.x(), j = v.y();
    if(i==0){ // sens clockwork celui du haut en 1er
        if(j==0){ // coin haut gauche
            neighbors[0] = i;
            neighbors[1] = j;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i;
            neighbors[7] = j;
        }else if(j<_ny-1){ // barre gauche
            neighbors[0] = i;
            neighbors[1] = j-1;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i;
            neighbors[7] = j;
        }else{ // coin bas gauche
            neighbors[0] = i;
            neighbors[1] = j-1;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j;
            neighbors[6] = i;
            neighbors[7] = j;
        }
    }else if(i<_nx-1){
        if(j==0){ // barre haut
            neighbors[0] = i;
            neighbors[1] = j;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }else if(j<_ny-1){ // milieu
            neighbors[0] = i;
            neighbors[1] = j-1;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }else{ // bare bas
            neighbors[0] = i;
            neighbors[1] = j-1;
            neighbors[2] = i+1;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }
    }else{
        if(j==0){ // coin haut droite
            neighbors[0] = i;
            neighbors[1] = j;
            neighbors[2] = i;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }else if(j<_ny-1){ // barre droite
            neighbors[0] = i;
            neighbors[1] = j-1;
            neighbors[2] = i;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j+1;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }else{ // coin bas droit
            neighbors[0] = i-1;
            neighbors[1] = j;
            neighbors[2] = i;
            neighbors[3] = j;
            neighbors[4] = i;
            neighbors[5] = j;
            neighbors[6] = i-1;
            neighbors[7] = j;
        }
    }
}

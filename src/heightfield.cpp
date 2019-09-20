#include "heightfield.h"
#include "poissondiscsampling.h"

#include <QDebug>

HeightField::HeightField(Box2 b2, int nx, int ny): ScalarField2(b2,nx,ny){}

HeightField::HeightField(Box2 b2, QImage img): ScalarField2(b2, img){}

float HeightField::height(Vec2 v){
    return value(v);
}

float HeightField::slope(Vec2 v){
    return gradient(v).length();
}

Vec3 HeightField::normal(Vec2 v){
    Vec2 grad = gradient(v);
    Vec3 n(-grad.x(),1,grad.y());
    n.normalize();
    return n;
}

ScalarField2 HeightField::slopeMap(){

    ScalarField2 sf(b2(),nx(),ny());
    for (int i = 0; i < nx(); ++i)
        for (int j = 0; j < ny(); ++j)
            sf.putValue(i,j,slope(Vec2(i,j)));

    return sf;
}

int HeightField::getLowerNeighbors(Vec2 pos, Vec2 neighbors[8], float diffHeights[8], float& totalDiffHeight){

    int nb_voisins = 0;
    float currentHeight = height(pos);
    totalDiffHeight = 0;

    for (int var_x = pos.x()-1; var_x <= pos.x()+1; ++var_x) {
        for (int var_y = pos.y()-1; var_y <= pos.y()+1; ++var_y) {

            if(var_x==pos.x() && var_y==pos.y()) continue; // centre

            if(!inSF2(var_x, var_y)) continue; // hors de la grille

            Vec2 neigh(var_x, var_y);
            float diffHeight = currentHeight - height(neigh); // distance en hauteur
            if(diffHeight < 0) continue; // voisin plus haut

            // On passe les données
            neighbors[nb_voisins] = neigh;
            diffHeights[nb_voisins] = diffHeight;
            totalDiffHeight += diffHeight;
            // Et on incrémente le compteur de voisins
            nb_voisins++;
        }
    }

    return nb_voisins;
}

Vec3 HeightField::biome(float e, float m, float minH, float maxH){
    e-= minH;
    maxH -= minH;
    m= (m+1)/2.0;

    // Fonction adaptée du code de redblobgame
    // https://www.redblobgames.com/maps/terrain-from-noise/

    if (e < 0.1 * maxH) return Vec3(67.0/255.0, 67.0/255.0, 122.0/255.0); // OCEAN
    if (e < 0.12 * maxH) return Vec3(147.0/255.0, 134.0/255.0, 119.0/255.0); // BEACH

    if (e > 0.8 * maxH) {
        if (m < 0.1) return Vec3(85.0/255.0, 85.0/255.0, 85.0/255.0); // SCORCHED
        if (m < 0.2) return Vec3(136.0/255.0, 136.0/255.0, 136.0/255.0); // BARE
        if (m < 0.5) return Vec3(188.0/255.0, 188.0/255.0, 171.0/255.0); // TUNDRA
        return Vec3(222.0/255.0, 222.0/255.0, 229.0/255.0); // SNOW
    }

    if (e > 0.6 * maxH) {
        if (m < 0.33) return Vec3(201.0/255.0, 210.0/255.0, 155.0/255.0); // TEMPERATE_DESERT
        if (m < 0.66) return Vec3(136.0/255.0, 153.0/255.0, 119.0/255.0); // SHRUBLAND;
        return Vec3(153.0/255.0, 171.0/255.0, 119.0/255.0); // TAIGA
    }

    if (e > 0.3 * maxH) {
        if (m < 0.16 ) return Vec3(201.0/255.0, 210.0/255.0, 155.0/255.0); // TEMPERATE_DESERT
        if (m < 0.50 ) return Vec3(136.0/255.0, 171.0/255.0, 85.0/255.0); // GRASSLAND
        if (m < 0.83 ) return Vec3(103.0/255.0, 147.0/255.0, 89.0/255.0); // TEMPERATE_DECIDUOUS_FOREST;
        return Vec3(67.0/255.0, 136.0/255.0, 85.0/255.0); // TEMPERATE_RAIN_FOREST
    }

    if (m < 0.16 ) return Vec3(210.0/255.0, 185.0/255.0, 139.0/255.0); // SUBTROPICAL_DESERT
    if (m < 0.33 ) return Vec3(136.0/255.0, 171.0/255.0, 85.0/255.0); // GRASSLAND
    if (m < 0.66 ) return Vec3(86.0/255.0, 153.0/255.0, 68.0/255.0); // TROPICAL_SEASONAL_FOREST
    return Vec3(51.0/255.0, 119.0/255.0, 85.0/255.0); // TROPICAL_RAIN_FOREST
}

Vec3 HeightField::perlinBiome(PerlinNoise& pn, QImage& img, Vec3 point, float minH, float maxH){
    //    float x = img.width() - ((sed.value(i,j) / maxSed) * img.width());

    if ( minH == maxH ) return Vec3(0.5, 0.5, 0.5);

    // PN pour x dans l'image
    float x = ( pn.noise( Vec2( point.x() , point.z() ) / 30.0 ) + 1 )/2 * (img.width());
    // Hauteur pour y dans l'image
    float y = img.height()-1 - ((point.y() - minH) / (maxH-minH) * (img.height() -1));

    // On renvoie la couleur
    return Vec3(
                img.pixelColor(x,y).red(),
                img.pixelColor(x,y).green(),
                img.pixelColor(x,y).blue()
                );
}

Vec3 HeightField::SF2Color(QImage& img, ScalarField2& sf2, Vec3 point, float minV, float maxV){
    if ( minV == maxV ) return Vec3(0.5, 0.5, 0.5);

    // Calcule la couleur en y dans l'image en fonction de la valeur dans l'interval minV maxV
    float y = img.height()-1 - (sf2.value(point.x(), point.z()) - minV) / (maxV - minV) * ( img.height() -1 );
    return Vec3(
                img.pixelColor(1, y).red(),
                img.pixelColor(1, y).green(),
                img.pixelColor(1, y).blue()
                );
}

void HeightField::createMesh(QString objName){
    ScalarField2 fake; // Sinon on fait une copie et non une référence pour rendre un parametre optionnel
    QString empty("");
    std::vector<Vec2> fakePos;
    createMesh(objName, NO_COLOR, empty, fake,fakePos);
}

void HeightField::createAFHColoredMesh(QString objName, QString colorChartName){
    ScalarField2 fake;
    std::vector<Vec2> fakePos;
    createMesh(objName, AF_COLOR, colorChartName, fake,fakePos);
}

void HeightField::createSF2ColoredMesh(QString objName, QString colorChartName, ScalarField2& sf2){

    std::vector<Vec2> fakePos;
    createMesh(objName, SF_COLOR, colorChartName, sf2,fakePos);
}

void HeightField::createAFHRoadColoredMesh(QString objName, QString colorChartName,std::vector<Vec2> pos){
    ScalarField2 fake;
    createMesh(objName, AFROAD_COLOR, colorChartName, fake,pos);
}


void HeightField::createMesh(QString objName, int mode, QString colorChartName, ScalarField2& sf2,std::vector<Vec2> pos){

    QFile file(objName+".obj");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed to create "+objName+".obj ";
        return;
    }

    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    float stepX, stepY;
    stepX = unitDiagonal().x();
    stepY = unitDiagonal().y();

    /* Calcul des sommets & couleurs */

    float minH,maxH;
    getRange(minH,maxH);

    PerlinNoise pn;

    QImage img;
    float minSF2, maxSF2;
    if (mode != NO_COLOR)   img = QImage(colorChartName);
    if (mode == SF_COLOR)   sf2.getRange(minSF2, maxSF2);

    for (int j = 0; j <ny(); ++j) {
        for(int i=0; i<nx(); i++){
            Vec3 ptbox = Vec3(i*stepX,value(i,j),j*stepY);
            Vec3 color;

            switch(mode){
            case NO_COLOR:
                flux << "v " << ptbox.x() << " " << ptbox.y() << " " << ptbox.z()<< endl;
                break;
            case AF_COLOR:
                color = perlinBiome(pn, img, ptbox, minH, maxH);
                //color = biome(ptbox.y(), pn.noise( Vec2(ptbox.x(), ptbox.z()) / 30 ), minH, maxH );
                flux << "v " << ptbox.x() << " " << ptbox.y() << " " << ptbox.z() << " "<< color.x()<<" "<<color.y()<<" "<<color.z()<< endl;
                break;
            case SF_COLOR:
                color = SF2Color(img, sf2, ptbox, minSF2, maxSF2);
                flux << "v " << ptbox.x() << " " << ptbox.y() << " " << ptbox.z() << " "<< color.x()<<" "<<color.y()<<" "<<color.z()<< endl;
                break;
            case AFROAD_COLOR:
                color = perlinBiome(pn, img, ptbox, minH, maxH);
                bool road = false;
                for(int k = 0; k < pos.size();k++){
                    if(Vec2(i,j) == pos[k]){
                        flux << "v " << ptbox.x() << " " << ptbox.y() << " " << ptbox.z() << " 125 125 125"<< endl;
                        road = true;
                        break;
                    }
                }
                if(!road)
                    flux << "v " << ptbox.x() << " " << ptbox.y() << " " << ptbox.z() << " "<< color.x()<<" "<<color.y()<<" "<<color.z()<< endl;
                break;
            }
        }
    }
    flux << endl;

    for (int j = 0; j <ny(); ++j) {
        for(int i=0; i<nx(); i++){
            flux << "vt "<<((float)i)/nx()<<" "<<((float)j)/ny()<< endl; // Coordonnée de texture bidon, a interpoler entre 0-1 pour la largeur nx*stepX/ny*stepY
        }
    }
    flux << endl;

    /* Calcul des normales de chaque sommet */

    for (int j = 0; j < ny(); ++j) {
        for(int i=0; i<nx(); i++){
            Vec3 normale = normal(Vec2(i,j));
            flux << "vn " << normale.x() << " " << normale.y() << " " << normale.z() << endl;
        }
    }
    flux << endl;

    /* Calcul des faces */

    for (int j = 0; j < ny()-1; ++j) { //probleme avec les normales d'indice 0?
        for(int i=1; i<nx()-1 ; i++){

            int vertexindice = index(i,j);
            int vertexindice2 = index(i,j+1);
            int vertexindice3 = index(i+1,j);
            int vertexindice4 = index(i+1,j+1);

            flux << "f " << vertexindice << "/"<<vertexindice<<"/" << vertexindice << " " << vertexindice2 << "/"<<vertexindice2<<"/" << vertexindice2 << " " << vertexindice3 << "/"<<vertexindice3<<"/" << vertexindice3 << endl;
            flux << "f " << vertexindice3 << "/"<<vertexindice3<<"/" << vertexindice3 <<" " << vertexindice2 << "/"<<vertexindice2<<"/" << vertexindice2 << " " << vertexindice4 << "/"<<vertexindice4<<"/" << vertexindice4 << endl;
        }
    }
}


QVector<Vec2> HeightField::findCitySpots(float minDistance, float planarRadius){
    QVector<Vec2> spots;

    // On a besoin d'un échantillonage

    // Grille
    /*
    for (int x = 0; x < nx(); x+=25) {
        for (int y = 0; y < ny(); y+=25) {
            // On réduit le champ de recherche de 50 en 50
            spots.push_back( Vec2(x,y) );
        }
    }
    */
    // Ou Poisson
    PoissonDiscSampling psd(25, 30, ny(), nx());
    psd.sampling();

    spots = psd.getPoints();

    // On trie par "planarité" des environs
    std::sort(spots.begin(), spots.end(), [&](Vec2 a, Vec2 b){
        return planarSum(a, planarRadius) < planarSum(b, planarRadius);
    });


    QVector<Vec2> citySpots;
    // On ajoute les plus "plats" éloignés d'une distance minimale minDistance
    for (int var = 0; var < spots.size(); ++var) {
        Vec2 spot = spots[var];
        bool checkDistance = true;
        for (int city = 0; city < citySpots.size(); ++city) {
            if ( (citySpots[city] - spot).length() < minDistance ){
                checkDistance = false;
                break;
            }
        }
        if (checkDistance) citySpots.push_back(spot);
    }

    return citySpots;
}

float HeightField::planarSum(Vec2 v, float radius){

    float sum = 0;
    int nb = 0;
    float currentHeight = height(v);

    // Fait la somme des différences de hauteurs dans un rayon et la divise
    // Plus ou moins une SSD sans le carré

    // On remarque que le relief sera tout autant capturé avec une croix/étoile, plutot que sur tout le radius,
    // on diminue ainsi énormément le temps d'éxécution

    // Grille entière

    /*
    for (int var_x = -radius; var_x < radius; ++var_x) {
        for (int var_y = -radius; var_y < radius; ++var_y) {

            if( var_x == 0 && var_y == 0 ) continue;
            if( !inSF2( v.x()+var_x, v.y()+var_y)) continue;

            sum += (currentHeight - value( v.x() + var_x , v.y() + var_y ));
            nb++;
        }
    }
    */

    // En etoile

    for (int var = -radius; var < radius; ++var) {
        if (var == 0) continue;

        //croix
        Vec2 vertical   (v.x()       , v.y()+radius );
        Vec2 horizontal (v.x()+radius, v.y()        );
        //etoile
        Vec2 diago_1    (v.x()+radius, v.y()+radius );
        Vec2 diago_2    (v.x()+radius, v.y()-radius );

        if( inSF2( vertical.x(), vertical.y() )){
            sum += ( currentHeight - height(vertical) );
            nb++;
        }
        if( inSF2( horizontal.x(), horizontal.y() )){
            sum += ( currentHeight - height(horizontal) );
            nb++;
        }
        if( inSF2( diago_1.x(), diago_1.y() )){
            sum += ( currentHeight - height(diago_1) );
            nb++;
        }
        if( inSF2( diago_2.x(), diago_2.y() )){
            sum += ( currentHeight - height(diago_2) );
            nb++;
        }
    }

    sum /= nb;
    return sum;
}

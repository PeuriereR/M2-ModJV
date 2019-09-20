#include "thermalerosion.h"
#include <iostream>
#include <QQueue>

ThermalErosion::ThermalErosion(){}

ThermalErosion::ThermalErosion(float angle, float epsi): angleAuRepos(angle), epsilon(epsi){}

void ThermalErosion::carriage(HeightFieldMulti& hfm, int iterations){

    srand (time(NULL));

    // Queue des piles non stables
    QQueue<Vec2> notStable;

    // Variables pour la stabilité
    Vec2 neighbors[8];
    float diffHeights[8];
    int nbNeighbors = 0;
    float totalDiffHeight = 0;

    HeightField hf = hfm.getHF();
    // On mettra hf a jour pour éviter de refaire cette fonction à chaque fois pour la vérification des angles

    // Initialisation
    for (int x = 0; x < hf.nx(); ++x) {
        for (int y = 0; y < hf.ny(); ++y) {
            Vec2 point(x,y);
            // Si point non stable, on push
            if( !stable( point ,hf, hfm, neighbors, diffHeights, totalDiffHeight, nbNeighbors) ){
                notStable.append( point );
            }
        }
    }

    int i = 0;
    while ( !notStable.empty() ){ // Stop condition

        if (iterations < 0) break; // Stop condition

        // On choisit une pile au hasard
        int ra = rand()%notStable.size();
        Vec2 stack = notStable.at(ra);
        notStable.removeAt(ra);

        // On vérifie si elle est toujours instable & récupère les voisins
        if ( stable( stack ,hf, hfm, neighbors, diffHeights, totalDiffHeight, nbNeighbors) ){
            continue;
        }

        // Traitement
        for (int neighbor = 0; neighbor < nbNeighbors; ++neighbor) {

            // Quantité de sédiment à déverser - proportionnel au total de la différence des hauteurs avec les voisins plus bas
            float qty = diffHeights[neighbor] / totalDiffHeight * epsilon;

            // Ajoute au voisin
            hf.addValue( neighbors[neighbor], qty );
            hfm.sediment.addValue( neighbors[neighbor], qty);

            // Ajout du voisin potentiellement non stable
            notStable.append( neighbors[neighbor] );
        }

        // Traitement des valeurs actuelles
        hf.addValue( stack, - epsilon);
        hfm.sediment.addValue( stack, - epsilon);

        // Ajout a la queue
        notStable.append( stack );

        iterations--;
        i++;
    }
    std::cout << "Erosion thermique achevée en "<<i<<" iterations."<<std::endl;

}

bool ThermalErosion::stable(Vec2 point, HeightField& hf, HeightFieldMulti& hfm, Vec2 neighbors[8], float diffHeights[8], float& totalDiffHeight, int& nbNeighbors){
    /* Angle<45 et sed>epsilon et possède aucun voisin plus bas = stable
     *
     * On récupère neighbors, diffHeights et totalDiffHeight ici en ayant besoin,
     * plutôt que de faire appel une deuxième fois à la fonction getLowerNeighbors avec les mêmes paramètres plus haut.
     * Il aurait été possible de faire l'inverse...
     */

    // Première condition
    if( hfm.sediment.value(point.x(), point.y()) <= epsilon ) return true;

    // Deuxième condition
    nbNeighbors = hf.getLowerNeighbors(point, neighbors, diffHeights, totalDiffHeight);
    if ( nbNeighbors ==0 ) return true;// Minimum local

    // Troisième condition

    // La grille ne donne pas une approximation du véritable angle avec les coordonnées,
    // On transforme donc nos coordonnées x,y dans le repère du monde (box)

    // Pour le calcul de l'angle
    Vec2 diag = hf.unitDiagonal();
    Vec2 coords(point.x()*diag.x(),point.y()*diag.y());

    Vec2 neighCoords;

    for (int neighbor = 0; neighbor < nbNeighbors; ++neighbor) {
        neighCoords = Vec2( neighbors[neighbor].x() * diag.x(), neighbors[neighbor].y() * diag.y() );
        // Pour chaque voisin plus bas, on vérifie l'angle
        if( (diffHeights[neighbor]/(coords - neighCoords).length()) > tan(angleAuRepos* M_PI / 180.0) )
            return false;
    }

    return true;
}

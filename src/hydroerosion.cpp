#include "hydroerosion.h"
#include "drainagearea.h"

HydroErosion::HydroErosion(){}

void HydroErosion::carriage(HeightFieldMulti& hfm, int iterations){
    // une fonction recursive serait plus lisible, mais potentiellement dangereuse avec beaucoup d'itérations

    DrainageArea d_area(hfm);
    d_area.spread();
    d_area.spread();
    d_area.spread();
    d_area.spread(); // Etale > humidité

    HeightField heightMap = hfm.getHF();

    // Pour chaque goutte, on simule le chemin
    for (int nbGoutte = 0; nbGoutte < iterations; ++nbGoutte) {
        // Obtention d'une position aléatoire
        Vec2 position = hfm.sediment.getRandomPos();
        int nbNeighbors;
        Vec2 neighbors[8];
        float diffHeights[8]; // Hposition - Hvoisin

        while (1){ // Le long du chemin

            // Obtention des voisins plus bas
            float totalDiffHeight = 0;
            nbNeighbors = heightMap.getLowerNeighbors(position, neighbors, diffHeights, totalDiffHeight);
            if(nbNeighbors == 0) break; // Fin du chemin, minimum local

            // On calcule les probas en fonction des distances en hauteur
            for (int neighbor = 0; neighbor < nbNeighbors; ++neighbor) {
                diffHeights[neighbor] /= totalDiffHeight;
            }

            // Obtention d'un float aléatoire entre 0 et 1
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            // On utilise la propriété d'accumulation =1 des probas
            int index = 0;
            float value = diffHeights[index];
            while( value < r ){
                // Quand on est dans la bonne range > on prend l'index
                index++;
                value+= diffHeights[index];
            }

            // Formule du Streampower
            float valenlevee = -k * sqrt(sqrt(d_area.value( position.x(), position.y() ))) * heightMap.slope(Vec2(position.x(),position.y()));

            // Ici on ne fait que enlever, on ne transporte pas réellement, meilleur résultat en /2

            float currentValue = hfm.sediment.value( position.x(), position.y() );

            if (currentValue < valenlevee)  {
                hfm.sediment.addValue( neighbors[index], hfm.sediment.value( position ) /2);
                hfm.sediment.putValue( position, 0.0);
            }
            else {
                hfm.sediment.addValue( neighbors[index], -valenlevee/2 );
                hfm.sediment.addValue( position, valenlevee);
            }
            // le /2 > dispersion progressive approximée

            position = neighbors[index]; // On continue le chemin de la goutte
        }
    }
}

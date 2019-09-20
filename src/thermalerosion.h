#ifndef THERMALEROSION_H
#define THERMALEROSION_H

#include "erosion.h"

// Classe pour l'application d'érosion thermique

class ThermalErosion : public Erosion
{
    // Variables de l'érosion
    float angleAuRepos = 45;
    float epsilon = 0.5;

    // Test de stabilités, renvoie également les voisins
    bool stable(Vec2 point, HeightField& hf, HeightFieldMulti& hfm, Vec2 neighbors[8], float diffHeights[8], float& totalDiffHeight, int& nbNeighbors);

public:
    ThermalErosion();
    ThermalErosion(float angle, float epsi);
    // ! Ne pas donner un espilon trop grand / angle trop petit ou le terrain ne sera jamais stable > maxiterations

    // Méthode de transport
    void carriage(HeightFieldMulti& hfm, int iterations);
};

#endif // THERMALEROSION_H

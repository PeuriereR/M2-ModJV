#ifndef POISSONDISCSAMPLING_H
#define POISSONDISCSAMPLING_H

// Classe extraite du projet POM fait en commun avec Eymard Baptiste

#include "vec2.h"
#include "disc.h"
#include <QImage>

/*! \class PoissonDiscSampling
   * \brief Class representative of a Poisson disc sampling
   *
   *  Class manages Poisson disc sampling to generate randon point
   * no closer to each other than a specified minimum distance, resulting in a more natural pattern
   * https://www.cct.lsu.edu/~fharhad/ganbatte/siggraph2007/CD2/content/sketches/0250.pdf
   */
class PoissonDiscSampling {
public:
    int r; /*!< Minimum distance between samples*/
    int k; /*!< Number of iterations before rejection*/
    QVector<Disc> grid; /*!< Grid for poisson disc sampling*/
    float w; /*!< Cell size in the grid*/
    // one cell -> one sample

    QVector<Vec2> active; /*!< Sample list to handle*/

    int cols ; /*!< Number of cols in grid*/
    int rows ; /*!< Number of rows in grid*/
    int height; /*!< Height of grid*/
    int width; /*!< Width of grid*/

    /*!
         *  \brief Constructor
         *
         *  \param r_p : Minimum distance between samples
         *  \param k_p : Number of iterations before rejection
         *  \param height_p : Height of grid
         *  \param width_p : Width of grid
         */
    PoissonDiscSampling(int r_p, int k_p, int height_p, int width_p);

    //! Execute Poisson disc sampling to generate randoms points
    void sampling();

    //! Return index for 1D array from an i and j
    inline int index(int i, int j);

    //! Returns all Vec2
    QVector<Vec2> getPoints();

    /*!
         *  \brief Draw all generated points on an image
         *
         *  \param img : image where draw points
         */
    void draw(QImage &img);

};

#endif // POISSONDISCSAMPLING_H

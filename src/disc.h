#ifndef DISC_H
#define DISC_H

// Classe extraite du projet POM fait en commun avec Eymard Baptiste

#include "vec2.h"

/*! \class Disc
   * \brief Class representative of a disc
   *
   *  Class manages dics
   */
class Disc {
public:
    Vec2 c; /*!< Center of disc*/
    float r; /*!< Radius of disc*/

    /*!
         *  \brief Constructor
         *
         *  \param _c : Center of disc
         *  \param _r : Radius of disc
         */
    Disc(Vec2 _c, float _r);
    Disc();

    /*!
         *  \brief Check if a point is in a disc
         *
         *  \param v : Point to test
         *  \return True if the point is in a disc, false if not
         */
    bool inDisc(Vec2 v);

    /*!
         *  \brief Check if two discs intersect
         *
         *  \param v : Disc to test
         *  \return True if discs intersect, false if not
         */
    bool intersect(Disc d);
};

#endif // DISC_H

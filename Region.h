#ifndef REGION_H
#define REGION_H
///@file

#include <vector>
#include <SFML-2.6.1/include/SFML/Graphics.hpp>
#include "LimitedArray2.h"
#include "Cell.h"

namespace engine {
    ///Regions are essentially game rooms. Regions are recursive (contain other, smaller regions).
    struct Region {
            LimitedArray2<Cell> *pCells;                    ///This region's cell array.
            std::vector<std::unique_ptr<Region>> children;  ///Children of this region.
            sf::Rect<unsigned> extentInParent;              ///Bounding rect in parent region.
            Region *pParent;                                ///Parent region or NULL for root.
    };
} //namespace engine

#endif //REGION_H

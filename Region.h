#ifndef REGION_H
#define REGION_H
///@file

#include <memory>
#include <vector>
#include <SFML-2.6.1/include/SFML/Graphics.hpp>
#include "Array2.h"
#include "Cell.h"

namespace engine {
    ///Regions are essentially game rooms. Regions are recursive (contain other, smaller regions).
    struct Region {
            ///This region's cell array or NULL.
            ///@note Regions far enough beyond the current zoom level(s) do not have a cell array.
            Array2<std::unique_ptr<Cell>> pCells;
            ///Children of this region.
            ///@note Regions far enough beyond the current zoom level(s) have no children.
            std::vector<std::unique_ptr<Region>> children;
            sf::Rect<unsigned> extentInParent;  ///<Extents (bounding rect) within parent region.
            Region *pParent;                    ///<Parent region or NULL for root.
    };
} //namespace engine

#endif //REGION_H

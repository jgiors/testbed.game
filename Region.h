#ifndef REGION_H
#define REGION_H
///@file

#include <memory>
#include <vector>
#include "LimitedArray2.h"
#include "Cell.h"

namespace engine {
    struct Region {
        LimitedArray2<Cell> cells;
        std::vector<std::unique_ptr<Region>> children;
        Region *pParent;
    };
}

#endif //REGION_H

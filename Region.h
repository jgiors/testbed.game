#ifndef REGION_H
#define REGION_H
///@file

#include "LimitedArray2.h"
#include "Cell.h"

namespace engine {
    class Region {
        public:
            Region(size_t MaxWidth, size_t MaxHeight, size_t Width, size_t Height)
            : cells(MaxWidth, MaxHeight, Width, Height)
            {}

            LimitedArray2<Cell> cells;
        private:
    };
}

#endif //REGION_H

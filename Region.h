#ifndef REGION_H
#define REGION_H
///@file

#include <vector>
#include "LimitedArray2.h"
#include "Cell.h"

namespace engine {
    class Region {
        public:
            Region(Region *pParent, size_t maxWidth, size_t maxHeight, size_t maxChildren);
            Region() = delete;
            Region(Region &) = delete;
            LimitedArray2<Cell>& cells() { return _cells; }
            std::vector<Region&>& children() { return _children; }
            Region* pParent() { return _pParent; }
        private:
            LimitedArray2<Cell> _cells;
            std::vector<Region&> _children;
            Region *_pParent;
    };
} //namespace engine

#endif //REGION_H

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

            void setDims(size_t width, size_t height) { _cells.setDims(width, height); } 

            LimitedArray2<Cell>& cells() { return _cells; }
            const LimitedArray2<Cell>& cells() const { return _cells; }

            std::vector<Region&>& children() { return _children; }
            const std::vector<Region&>& children() const { return _children; }

            Region* parent() { return _pParent; }
            const Region* parent() const { return _pParent; }
            void parent(Region *pParent) { _pParent = pParent; }

        private:
            LimitedArray2<Cell> _cells;
            std::vector<Region&> _children;
            Region *_pParent;
    };
} //namespace engine

#endif //REGION_H

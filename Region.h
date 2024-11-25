#ifndef REGION_H
#define REGION_H
///@file

#include <vector>
#include <SFML-2.6.1/include/SFML/Graphics.hpp>
#include "LimitedArray2.h"
#include "Cell.h"

namespace engine {
    ///
    class Region {
        public:
            Region(Region *pParent);
            Region() = delete;
            Region(Region &) = delete;

            LimitedArray2<Cell>* pCells() { return _pCells; }
            const LimitedArray2<Cell>* pCells() const { return _pCells; }
            void pCells(LimitedArray2<Cell> *p) { _pCells = p; }

            std::vector<Region&>& children() { return _children; }
            const std::vector<Region&>& children() const { return _children; }

            Region* parent() { return _pParent; }
            const Region* parent() const { return _pParent; }

            // size_t widthInParent;
            // size_t heightInParent;

        private:
            LimitedArray2<Cell> *_pCells;
            std::vector<Region&> _children;
            Region *_pParent;
    };
} //namespace engine

#endif //REGION_H

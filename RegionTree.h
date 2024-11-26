#ifndef REGIONTREE_H
#define REGIONTREE_H

#include <memory>
#include <vector>
#include "Region.h"

namespace engine {
    ///Region tree for tracking existing regions. Does not handle expansion of regions or descendant
    ///removal, which are PCG responsibilities.
    class RegionTree {
    public:
        RegionTree() : _activeRegion(_root) {}
        RegionTree(RegionTree&) = delete;
        RegionTree& operator=(RegionTree&) = delete;

        const Region& root() const { return _root; }
        Region& root() { return _root; }

        const Region& activeRegion() const { return _activeRegion; }
        Region& activeRegion() { return _activeRegion; }
        void activeRegion(Region &r) { _activeRegion = r; }
    
    private:
        Region _root;
        Region &_activeRegion;
    };
} //namespace engine

#endif //REGIONTREE_H

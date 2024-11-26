#ifndef REGIONSTACK_H
#define REGIONSTACK_H

#include <memory>
#include <vector>
#include "Region.h"

namespace engine {
    class RegionCache {
    public:
    
    private:
        std::vector<Region> cache;
        Region *pRoot;
        Region *pCurrent;
    };
} //namespace engine

#endif //REGIONSTACK_H

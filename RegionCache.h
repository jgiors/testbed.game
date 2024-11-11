#ifndef REGIONCACHE_H
#define REGIONCACHE_H

#include <memory>
#include <vector>
#include "Region.h"

namespace engine {
    class RegionCache {
    public:
        ///@todo
    private:
        std::vector<std::unique_ptr<Region>> cache;
    };
} //namespace engine

#endif //REGIONCACHE_H

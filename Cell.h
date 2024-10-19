#ifndef ENGINE_CELL_H
#define ENGINE_CELL_H
///@file

#include <vector>

namespace engine {
    ///Cell, which is a recursive set of child cells, though I'm not rethinking that...
    struct Cell {
        std::vector<std::vector<Cell>> children;
    }
}

#endif //ENGINE_CELL_H

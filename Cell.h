#ifndef ENGINE_CELL_H
#define ENGINE_CELL_H
///@file

namespace engine {
    ///Cell, which is a recursive set of child cells, though I'm now rethinking that...
    struct Cell {
        enum class State {
                uninitialized,
                empty,
                occupied,
                filled,
        };
        State state;
    };
}

#endif //ENGINE_CELL_H

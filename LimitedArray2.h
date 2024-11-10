#ifndef ARRAY2_H
#define ARRAY2_H

namespace engine {
    ///Limited 2-dimensional bounds-checked array class. Elements are allocated at construction to
    ///support maximum dimensions. Dimensions may be adjusted after construction.
    template <typename T>
    class LimitedArray2 {
        public:

        private:
            std::vector<T> elements;
            
    };
} //namespace engine

#endif //ARRAY2_H

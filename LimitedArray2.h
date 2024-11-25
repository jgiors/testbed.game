#ifndef ARRAY2_H
#define ARRAY2_H
///@file

#include <cstddef>
#include <cassert>
#include <vector>

namespace engine {
    ///Limited 2-dimensional bounds-checked array class, indexed as array[column][row].
    ///Elements are allocated at construction and can not be resized.
    template <typename T>
    class LimitedArray2 {
        public:
            LimitedArray2(size_t Width, size_t Height)
            : _width(Width), _height(Height), _elements(Width * Height)
            {
            }

            LimitedArray2() = delete;
            LimitedArray2(LimitedArray2&) = delete;
            LimitedArray2& operator=(LimitedArray2&) = delete;

            ///Column which makes double indexing, i.e. array[column][row] possible: Column is
            ///returned by LimitedArray2::operator[column], then Colmun::operator[row] resolves
            ///to the element at array[column][row].
            class Column {
                public:
                    Column(size_t _column, std::vector<T> &Elements, size_t Width, size_t Height)
                    : column(_column), elements(Elements), width(Width), height(Height)
                    {
                        assert(column < width);
                    }

                    T& operator[](size_t row) {
                        assert(row < height);
                        return elements[row * width + column];
                    }

                    const T& operator[](size_t row) const {
                        assert(row < height);
                        return elements[row * width + column];
                    }

                private:
                    std::vector<T> &elements;
                    size_t column;
                    size_t width;
                    size_t height;
            };

            Column operator[](size_t column) {
                assert(column < _width);
                return Column(column, elements, _width, _height);
            }

            const Column operator[](size_t column) const {
                assert(column < _width);
                return Column(column, elements, _width, _height);
            }

            size_t width() const { return _width; }
            size_t height() const { return _height; }

            ///Get linear elements.
            std::vector<T>& elements() { return elements; }
            ///Get linear elements, read-only.
            const std::vector<T>& elements() const { return elements; }

        private:
            std::vector<T> _elements;
            size_t _width;
            size_t _height;
    };
} //namespace engine

#endif //ARRAY2_H

#ifndef ARRAY2_H
#define ARRAY2_H
///@file

#include <cstddef>
#include <cassert>
#include <vector>
#include <SFML-2.6.1/include/SFML/Graphics.hpp>

namespace engine {
    ///Limited 2-dimensional bounds-checked array class, indexed as array[column][row],
    ///which matches the order of (x,y) coordinates.
    ///Elements are allocated at construction and can not be resized.
    ///@note    Items are in column-major order which is contrary to usual C++ row-major order.
    template <typename T>
    class LimitedArray2 {
        public:
            LimitedArray2(sf::Vector2u Dims)
            : _elements(Dims.x * Dims.y), _dims(Dims)
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
                    Column(std::vector<T> &Elements, unsigned Base, unsigned height)
                    : elements(Elements), base(Base), height(Height)
                    {
                    }

                    T& operator[](unsigned row) {
                        assert(row < height);
                        return elements[base + row];
                    }

                    const T& operator[](unsigned row) const {
                        assert(row < height);
                        return elements[base + row];
                    }

                private:
                    std::vector<T> &elements;
                    unsigned base;
                    unsigned height;
            };

            ///Obtain column for double-indexing.
            Column operator[](size_t column) {
                assert(column < _width);
                return Column(elements, column * _height, height);
            }

            ///Obtain column for double-indexing.
            const Column operator[](size_t column) const {
                assert(column < _width);
                return Column(elements, column * _height, height);
            }

            sf::Vector2u dims() const { return _dims; }

            ///Get linear elements.
            std::vector<T>& elements() { return _elements; }
            ///Get linear elements, read-only.
            const std::vector<T>& elements() const { return _elements; }

        private:
            std::vector<T> _elements;   ///<Linear elements of the 2D array.
            sf::Vector2u _dims;         ///<Array dimensions.
    };
} //namespace engine

#endif //ARRAY2_H

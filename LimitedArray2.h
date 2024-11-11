#ifndef ARRAY2_H
#define ARRAY2_H

#include <assert>
#include <vector>

namespace engine {
    ///Limited 2-dimensional bounds-checked array class. Index is x, y order, i.e. Array[x][y].
    ///Elements are allocated at construction to support maximum dimensions. Dimensions may be
    ///adjusted after construction, but may not exceed the maximum.
    template <typename T>
    class LimitedArray2 {
        public:
            LimitedArray2(size_t MaxWidth, size_t MaxHeight, size_t Width, size_t Height)
            : maxWidth(MaxWidth), maxHieght(MaxHeight), width(Width), height(Height), elements(MaxWidth * MaxHeight)
            {
                assert(maxWidth > 0 && maxHeight > 0);
                assert(width < maxWidth && height < MaxHeight);
            }

            LimitedArray2() = delete;
            LimitedArray2(LimitedArray2&) = delete;
            LimitedArray2& operator=(LimitedArray2&) = delete;

            ///Set new dimensions. Must satisfy (Width <= maxWidth && Height <= maxHeight).
            ///@attention Does not clear the elements of the array.
            void setDims(size_t Width, size_t Height) {
                assert(Width < maxWidth);
                assert(Height < maxHeight);
                width = Width;
                height = Height;
            }

            class Column {
                public:
                    Column(size_t _column, std::vector<T> &Elements, size_t Width, size_t  Height)
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
                assert(column < width);
                return Column(column, elements, width, height);
            }

            const Column operator[](size_t column) const {
                assert(column < width);
                return Column(column, elements, width, height);
            }

            size_t getWidth() const { return width; }
            size_t getHeight() const { return height; }
            size_t getMaxWidth() const { return maxWidth; }
            size_t getMaxHeight() const { return maxHeight; }

            ///Get linear elements.
            std::vector<T> elements& getElements() { return elements; }
            ///Get linear elements, read-only.
            const std::vector<T> elements& getElements const { return elements; }

        private:
            std::vector<T> elements;
            size_t width;
            size_t height;
            size_t maxWidth;
            size_t maxHeight;
    };
} //namespace engine

#endif //ARRAY2_H

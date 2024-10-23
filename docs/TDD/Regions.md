Regions TDD
===========

Background
----------

### Motivation

While working on this project, I had an idea to recurse in regions within a region instaed of recursing by each cell (if this is not clear, continue on and come back to this later). I was about to implement cells (as class engine::Cell), but I realized that there is a significant and fundamental difference between the two concepts. Hence, I need to delve into the design requirements in detail and see what emerges.

### Cells

The game world consists of recursive layers of cells, where the height and width of each layer is an integer multiple of the previous layer. The primary cell states are occupied and empty. However, there is at least one variation: filled (fully occupied). It is possible that, in later variations, there may be cells which act as empty, but on zoom, actually have some occupied subcells (think of it as dust).

My original design concept was to start with a cell, then recurse to the child cells of that cell, operating on each layer in turn.

Concept
-------

### What is a region?

The new concept is based on *regions* instead of *cells*. Regions are still made of cells and can be of arbitrary shape, though their extent is limited to prevent excessive recursion and memory consumption. Cells within a region may be occupied, empty, filled, or dust.

### PCG of regions

The PCG processes a region by removing cells from the region's structure (marking them empty or dust). It might also mark some occupied cells as permanently filled. It is not expected to convert empty cells into occupied or filled. Once the PCG finishes processing a region, it breaks the region into sub-regions, then recursively processes them.

### Example

To reduce the complexity of the example, assume a region contains 4 x 4 cells:

```
****
****
****
****
```

Now assume the PCG creates paths through the region:

```
** *
** 
   *
* **
```

The lower-right corner contains a 2 x 2 region:

```
 *
**
```



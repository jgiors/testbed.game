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

The new concept is based on #regions# instead of #cells#. Regions are still made of cells and can be of arbitrary shape, though their extent is limited to prevent excessive recursion and memory consumption. Cells within a region may be occupied, empty, filled, or dust.

### PCG of regions

The PCG processes a region by removing cells from the region's structure (marking them empty or dust). It might also mark some occupied cells as permanently filled. It is not expected to convert empty cells into occupied or filled. Once the PCG finishes processing a region, it breaks the region into sub-regions, then recursively processes them.

### Example

To reduce the complexity of the example, assume a region contains 4 x 4 cells:

```
####
####
####
####
```

Now assume the PCG creates a path through the region:

```
#·##
#··· 
···#
#·##
```

It contains four sub-regions (aka child regions). From upper-left to lower-right they are:

```
#            ##             #             ·#
#                                         ##
```

The width-by-height sizes of the sub-regions are: 1 x 2, 2 x 1, 1 x 1, 2 x 2

When the last region (from the lower-right) is recursed, it is multiplied by the scale factor of 2, which results in the following:

```
··##
··##
####
####
```

The other sub-regions would be recursed similarly. In the case of this region, the PCG algortihm would cut a path through the region, which might look like the following:

```
··##
··#·
#···
##·#
```

The algorithm continues recursively through sub-regions until reaching the current zoom level.

Parameters
----------

- Wmax x Hmax = maximum region dimensions
    - The dimensions are the number of subcells wide by tall (height).
    - I expect Wmax = Hmax, but the dimensions will be tracked separately, just in case.
- Z = zoom factor = number of sub-cells wide/tall per cell
    - How much zoom is applied at each level.
    - Also happens to determine the cell/sub-cell relationship.
        - Each cell contains Z x Z subcells because height and width are constrained by zoom and must be equal.

Maximum sub-region size
-----------------------

### Sub-region, region, and zoom relationship

- Since there are Z x Z subcells per cell, a sub-region of dimension W x H contains W*Z x W*H sub-cells.
- Therefore, in order to prevent exceeding Wmax x Hmax:

    Wsubmax * Z = Wmax  ->  Wsubmax = Wmax / Z
    Hsubmax * Z = Hmax  ->  Hsubmax = Hmax / Z

### Numbers in practice

See RegionDimensions.ods



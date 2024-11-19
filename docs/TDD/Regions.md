Regions TDD
===========

Background
----------

### Motivation

While working on this project, I had an idea to recurse in regions within a region instaed of recursing by each cell (if this is not clear, continue on and come back to this later). I was about to implement cells (as class engine::Cell), but I realized that there is a significant and fundamental difference between the two concepts.

### Cells

The game world consists of recursive layers of cells, where the height and width of each layer is an integer multiple of the previous layer. The primary cell states are occupied and empty. Additional states are[^dust]:

- Filled: A cell which is entirely filled solid and impenetrable (all subcells are recursively filled).
- Uninitialized: Cell state before it has been assigned a state. Uninitialized cells should never be encountered during gameplay.

My original design concept was to start with a cell, then recurse to the child cells of that cell, operating on each layer in turn.

Concept
-------

### What is a region?

#### Concept

The new concept is based on *regions* instead of *cells*. A region is a contiguous, connected group of cells, and can be of arbitrary shape, though their extent is limited to prevent excessive memory consumption and processing time. Cells within a region may be occupied, or filled. Occupied cells subdivide into subcells. Filled cells are completely filled and impassable.

#### class `Region`

In order to simplify working with regions, a region is stored in a rectangular 2D array. The 2D array's dimensions are chosen so that the conceptual region fits within the rectangular area. Empty cells surround the region to fill out the remainder of the rectangle. [^dust]

### PCG of regions

The PCG processes a region by removing cells from the region's structure (marking them empty). It might also mark some occupied cells as permanently filled. It is not expected to convert empty cells into occupied or filled.

Once the PCG finishes processing a region, it breaks the region into sub-regions, which are contiguous groups of cells. The PCG then expands each sub-region by the zoom factor (explained below) and recursively processes it as a region of the next zoom level.

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

Parameters and their relationships
----------------------------------

### Region dimensions and area

- Width x Height := Dimensions of a region's bounding box, measured in linear cells.
- Area := Area of region's bounding box in cells = Width * Height
- MaxArea := Maximum number of cells in region's bounding box.
    - Area = Width * Height <= MaxArea
- Additional constraint: MinWidth <= Width <= MaxWidth ; MinHeight <= Height <= MaxHeight
    - Prevents excessively thin (very wide or very tall) regions.
    - Potential violations of these constraints need to be handled, e.g. by splitting the region or making it solid (not enterable).

### Child Regions

Child regions are defined in relationship to their parent region.

#### Zoom factor

- ZoomFactor := Integer number of linear sub-region cells per parent region cell. Varies per region. Horizontal and vertical are same factor.
    - Constraint: MinZoomFactor <= ZoomFactor <= MaxZoomFactor
- AreaMultiplier := ZoomFactor ^ 2 = Cell area multiplier when comparing child region size in parent cells vs child cells.
- ChildWidth x ChildHeight := Dimensions of a region's bounding box in its parent's zoom level.
- The relationship between child dimensions and child cells: ChildWidth * ChildHeight * ZoomFactor^2 = Area <= MaxArea
- Therefore: ZoomFactorTarget = sqrt(MaxArea / (ChildWidth * ChildHeight))
- The ZoomFactorTarge must be compared against other constraints to determine the actual ZoomFactor to use.

#### Additional constraints

- MaxChildren := Limit on number of child regions per region.
- MaxProductiveChildren := Limit on number of child regions which may propagate further child regions.
    - Note: Filled child regions do not propagate, so when this limit is hit, action must be taken. One possibility is to make the region solid.
    - The potential total number of productive descendants at a zoom level increases exponentially: MaxProductiveCellsAtZoomLevel = MaxArea * (MaxProductiveChildren ^ ZoomLevel)
- MaxUnroductiveChildren := Limit on number of child regions which can not propagate further child regions.
    - Obviously: MaxUnroductiveChildren + MaxProductiveChildren = MaxChildren

#### Example calculations

See RegionDimensions.ods

Sub-region bounding box overlap
-------------------------------

### Explanation

- A sub-region will be processed by finding its bounding box and expanding it out into a region to be processed.
- This means that bounding boxes are likely to overlap, which in turn means that there is likely to be redundant processing in the overlapping areas. I do not know how much additional processing this will cause. It is difficult to determine what the maximum amount of overlap is.
- Also, it appears that, the cases which have the worst overlap tend to be skinny pieces that, upon the next recursion, will not produce high overlap. In other words, it seems that things would balance out a bit should the worst-case scenario arise.
- I will take a look at this again when I can. I would like to be able to calculate a reasonable value, but don't yet know how to do that.

### Example

I imagine that the worst case example looks something like this:

```
#·#·#####·###
··#·····#···#
#·#####·#·#·#
#·········#··
#####·#####·#
```

TODO: Fix this explanation and/or the above example! The above region 13 x 5 and most of the overlapping child regions are 5 x 3.

In one 5 x 5 region, we have 5 regions that are 3 x 3.

Region stack
------------

### Motivation

The avatar will be in a particular region at a particular zoom level. Above that zoom level will be a series of regions, back to the root region at the root level. It makes sense to store this as a LIFO stack.

### Memory pre-allocation

The region stack will be pre-allocated upon startup so that no dynamic allocations are made during gameplay.

### Partial recursion complications

With expected region PCG parameters, correctly defining a region will require some amount of recursion into child regions and further descendant regions.

This has implications for a stack implementation:

- Allocating and executing the PCG on a single region at a particular zoom level must account for the creation of potentially many regions.
    - This must be taken into account when attempting to determine how many regions (and cells) to pre-allocate.
- The PCG must know when to stop recursing.
- The PCG must be aware of pre-existing regions when processing a region. That region will already exist on the stack, so in reality, the PCG must recurse down into the children/descendants and allocate/process only the bottom level of the cache.

TODO: Note that there are basically 2 parts: (1) the cells region in the parent, (2) the cells making up the region at its own zoom level. It is possible for (1) to exist without (2).

### calculations

TODO: Calculations

The basic ideas are something like this:
- Stack starts with a region at zoom level 0 and there is also a current region at CurrentZoomLevel.
    - However, the final regions will be at some zoom level >= CurrentZoomLevel.
- A region can have up to MaxUnroductiveChildren which will end up with a limited amount of recursion.
    - For initial designs, we can assume these are solid filled, so they will only need to track the cells region in the parent, and can be assumed to be of that size.
- A region can have up to MaxProductiveChildren, and each of those can have up to MaxProductiveChildren as well, up to some zoom level delta.
    - The total number of possible productive children, plus the region itself, will be = MaxProductiveChildren ^ (ZoomLevelDelta + 1).
    - We would also need to account for which of these require nodes to be allocated, and which don't.
- That only covers the data for fleshing out one region.
- We need to account for each level of zoom.
    - However, the additional for each level of zoom will be a little less than what the above implies because some of the regions for the child region will have already been allocated when processing the parent.
- Probably need to analyze by looking at the differential for each added zoom level, rather than trying to directly compute the total (then add back in the top few layers which cannot be handled by this differential).


[^dust]: It is possible that, in a future version of the game, there may be cells which act as empty, but on zoom, actually have some occupied subcells (think of them as dust). This is not compatible with the current design (2024-10-26) since sub-regions now have entry and exit points, and zoom can not be activated arbitrarily. Should the design change, dust may be reevaluated.

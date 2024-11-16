Per-Region Zoom Factor Proposal
===============================

Background
----------

The original Zoomer game design called for a constant integer zoom factor which is applied each time a zoom-in into a child region occurs (and the reciprocal is applied upon zoom-out).

In order to bound the size of a region while maintaining a constant zoom factor, the size of child regions (relative to the parent region) must be constrained as follows:

```
ChildWidth <= ParentWidth / ZoomFactor
ChildHeight <= ParentHeight / ZoomFactor
```

With a reasonable zoom factor and region dimensions that are not excessive, the allowable child region dimensions feel excessively limited.  (sometimes as little as 3 cells).

Proposal Statement
------------------

1. Do not constrain the zoom factor to be constant.
2. Continue to constrain the zoom factor to be an integer.
3. Constrain the zoom factor between minimum and maximum bounds.
4. Regions continue to be an integral number of idetically-sized, square cells.

> [!NOTE]
> Item 4 is a more concise way of stating the intuitive, but potentially ambiguous, notion that *"zoom should be constant within a region"*.

Motivation
----------

Since the current design is for the avatar to always be within one region at any given moment, it is no longer necessary to match the sizes of cells across different regions, so long as each individual region is composed of identically sized cells.

By allowing the zoom factor of each region to be determined independently, it will be possible to support a larger range of child region sizes, while also allowing child regions to have a larger number of cells when zoomed in. This should allow regions to be more interesting for players, where the original design might feel cramped in many cases.

Analysis
--------

### Calculations

- Zoom factor is limited to a particular range: Zmin <= ZoomFactor <= Zmax
- A region is defined within a rectangle with dimensions Width x Height
- The maximum number of cells in a region is MaxCells:  Width * Height <= MaxCells
- For a given ZoomFactor, the cell multiplier is ZoomFactor squared: CellMultiplier = ZoomFactor^2
- Therefore, for a subregion, the dimensions must satisfy: SubWidth * SubHeight * CellMultiplier <= MaxCells
- This results in: ZoomFactor <= sqrt(MaxCells / (SubWidth * SubHeight))
    - If it falls outside the range:
        - For ZoomFactor > Zmax: ZoomFactor = Zmax
        - For ZoomFactor < Zmin: Split up the region
    - Will also split regions that are too skinny (excessively wide or tall). This is a design consideration, not a technical limitation.

### Pros

- Regions will on average contain more cells, providing more variety of regions (and hopefully more player interest).
- Individual regions will more efficiently use the pre-allocated cell array.
- Less region splits needed to meet constraints.
    - Corollary: More flexibility in region shapes.

### Cons

- Because some regions have a small relative zoom factor, it will be necessary to store more layers of descendants.
    - This could lead to larger quantities of descendants (despite smaller zoom factor) because of exponential nature of fan-out.
    - Makes it more difficult to predict the upper bound of allocations.
        - (But can be addressed by enforcing limits by removing regions, converting some regions to impenetrable, or starting over on bad result.)
- Related logic is not quite as simple (but not very complex).
- The greater variability of potential region shapes and zoom factors increases the possibility space for testing.
- If the game design moves away from single-region exploration, per-region zoom factors may become problematic.

Conclusion
----------

Per-regions zoom factors have several advantages. Player experience is expected to be improved due to the greater variety of regions that can be produced. The tradeoffs in somewhat greater complexity (which is not anticipated to be excessive) and likely higher memory usage are probably worth the improved player experience.
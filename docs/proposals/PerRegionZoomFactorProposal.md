Per-Region Zoom Factor Proposal
===============================

Background
----------

The original Zoomer game design called for a constant integer zoom factor which is applied each time a zoom-in into a child region occurs (and the reciprocal is applied upon zoom-out).

In order to bound the size of a region while maintaining a constant zoom factor, the size of child regions (relative to the parent region) must be constrained as follows:

```
ChildWidth <= ParentWidth / ZoomFactor
ChildHeight <= ParentHeigh / ZoomFactor
```

With a reasonable zoom factor and region dimensions that are not excessive, the allowable child region dimensions feel excessively limited.  (sometimes as little as 3 cells).

Proposal Statement
------------------

1. Do not constrain the zoom factor to be constant.
2. Continue to constrain the zoom factor to be an integer.
3. Constrain the zoom factor between minimum and maximum bounds.
4. Regions continue to be an integral number of same-sized, square cells.

> [!NOTE]
> Item 4 is a more concise way of stating the intuitive, but potentially ambiguous, notion that *"zoom should be constant within a region"*.

todo

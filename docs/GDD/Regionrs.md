Regions GDD
===========

Cells
-----

The game world is recursively composed of layers of cells. Each cells contains Z x Z sub-cells, which are cells of the next layer. Z is the zoom factor, which is how much zoom-in occurs at each layer.

Regions
-------

A region is a contiguous block of connected cells. Upon zoom-in the region is composed of sub-regions, forming a game room to be navigated.

### Entry/exit points

Regions have entry points, which is how zoom-in is initiated. Once inside, the exits are at the points where the entry points were.

#### TBD

- How are entry points indicated to player?
- How is entry (zoom) initiated?
- How are exits indicated?
- How is exit initiated?

### Escape out

The player can choose to escape out of the current region and return to the entry point where they started.

#### TBD

- How to escape out?

### Root region

The root region is the farthest zoomed-out region that is the root of the entire game world (aka universe).

### Home region

The game begins in the home region. The home region is not the root region. It is a region several zoom levels down from the root region.

The user will find zoom-in abilities early on, and after getting, say 3 or 4 levels of zoom, the player will be able to find a "-1" zoom ability, which grants the ability to zoom out from the home region (hopefully this is an "aha moment").

Eventually, the player will eventually be able to zoom out all the way to the root region.

Additional mechanics
--------------------

### Return home

There should also be a special "return home" to return to the home region starting point.

This should work even when zoomed out beyond the initial region. However, in this situation, it is not currently clear what should happen if the user returns home, then escapes out, since there may not be defined path from the root region to the initial gameplay region. Probably, the exit points that the player used (beyond the home region) should be remembered so they can be used to solve this problem.

General TDD
===========

This document covers genearl TDD requirements.

Memory allocation
-----------------

### Standard techniques

Just use standard C++ memory allocation techniques.

### Region cache

Regions will be cached so the PCG can be more complex without slowing down rendering and updates.

### Region stack

A region stack is used to track the regions the avatar is inside. However, region memory is allocated from the heap and there is no attempt to force memory allocations to be strictly LIFO. It is not certain what the final regions design will be, and a LIFO is too restrictive for most designs. This will be revisited at an appropriate point in development.

### Optimization

Optimization of memory allocation techniques will likely be necessary, but this will be addressed later in the project when the design is more stable.

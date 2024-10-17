Milestone 0: PCG Platformer, No Zoom
====================================

Brief
-----

This is the design document for milestone 0 which also covers technical design.

Objective
---------

Create a minimal playable game that represents a starting point for implementing the rest of the project: A playable PCG level with a user-controlled avatar, but without the zoom feature, which will be implemented in a future milestone.

Background
----------

I was having difficulthy starting this project because there are too many things that need to be done. I added issues to the GitHub project, but they were disorganized and not comprehensive. I really need to take a step back and summarize everything in one place.

Requirements
------------

These items are required in order to meet the objective of this milestone and are described in a hierarchy:

- PCG "level" generator: Must generate a one-screen playable level. Preferably designed as a block-of-subblocks.
    - Blocks. Blocks recursively contain other blocks, which are called sub-blocks.
    - PCG algorithm which "carves" sub-block shapes out of a block. Does not recurse at this time.
- Update loop and time handling.
    - Basic time handling and error accumulation.
    - Fixed rate update, i.e. `dt` is fixed, aka physics update.
    - Variable rate update, aka frame update.
- User input handling.
    - 4-way arrows input.
    - Jump key (space).
- Avatar physics.
    - Second order integrator.
    - Left/right acceleration with max velocity, but not too drifty.
    - Jump upward acceleration up to limit (then user input no longer affects). 
    - Gravity.
- Avatar collision.
    - Detection of sub-blocks.

Avoid
-----

Items to avoid at this time, stated as "Do not ...". These are contraindicated at this time in order to reduce complexity.

- Do not support zoom.
    - Do not recurse sub-blocks.
- Do not scroll the screen.
    - The PCG "level" should fit on a single screen.
    - No camera. Just use a fixed transformation matrix.

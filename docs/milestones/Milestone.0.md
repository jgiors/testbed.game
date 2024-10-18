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

- PCG "level" generator: Must generate a one-screen playable level. Preferably designed as a cell-of-subcells.
    - Level does not need to be guaranteed to be completable.
    - Cells. Cells recursively contain other cells, which are called subcells.
    - PCG algorithm which "carves" subcell shapes out of a cell. Does not recurse at this time.
- Update loop and time handling.
    - Basic time handling and error accumulation.
    - Fixed rate update, i.e. `dt` is fixed, aka physics update.
    - Variable rate update, aka frame update.
- Rendering
    - Each subcell is 1 unit by 1 unit.
    - Avatar is just a rectangle, approximately 0.5 units wide by 0.75 units tall.
- User input handling.
    - 4-way arrows input.
    - Jump key (space).
- Avatar physics.
    - Second order integrator.
    - Left/right acceleration with max velocity, but not too drifty.
    - Jump upward acceleration up to limit (then user input no longer affects).
    - Can only land on top of subcells. Slides along sides.
    - Gravity.
- Avatar collision.
    - Detection of subcells.

Avoid
-----

Items to avoid at this time, stated as "do not", "can not", etc. These are contraindicated at this time in order to reduce complexity.

- Do not support zoom.
    - Do not recurse subcells.
- Do not scroll the screen.
    - The PCG "level" should fit on a single screen.
    - No camera. Just use a fixed transformation matrix.
- Avatar can not climb walls.

Plan
----

Proposed sequence for implementing the requirements.

### Overarching items

These are overaching things that need to be done, but which will not be called out again in the following sections.

- Add configurable items to `config.json`, e.g. world-to-screen scaling, number of sub-cells, avatar size, physics params.
- Add logging where appropriate.

### Random subcells render test

- `engine::Cell` class
    - N x N array of subcells
        - N = 32 for now
        - Implemented as 2 x `vector`? arrays? something else?
    - State: undefined, occupied, empty
- Random "PCG" which randomly sets/clears all subcells of a cell.
- Set up view transformation for at least 32 subcells tall.
- Render subcells of cell.

### Basic PCG

- Carves out a reasonable-looking "level" of subcells within a cell.

### Update loop

- Basic time handling and error accumulation.
- Fixed rate update, i.e. `dt` is fixed, aka physics update.
- Variable rate update, aka frame update.
- Render an avatar rectangle which moves back and forth (not under user control yet).

### Avatar physics, not user controlled yet

- Left/right acceleration with max velocity, but not too drifty.
- Gravity.
- Jump upward acceleration up to limit (then user input no longer affects).
- Simple automated motion test, possibly where the avatar block moves left/right and bounces (jumps) off an invisible floor.  

### Avatar collision

- Detection of subcells.
- Can only land on top of subcells. Slides along sides.
- Change the previous automated demo to move/jump on cells in the "level".

### User control of avatar

- 4-way arrows input.
- Jump key (space).

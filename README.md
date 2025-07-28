# spaceships
A simple game written in C++ using the SFML-3.0 library that I always wanted to make. Or at least make something similar.
# todo
- Update the Menu to draw sprites using ShipImage
- Update the introduction in the README (this document)
- Fix the... intersting problems with origin, rotation etc
- Investigate the stupid framerate counter giving absurdly high values and slowly decreasing as game is running
- Fix the mess with spaceship cores and the remnants of the tree-like structure that was originaly intended for ship parts (not that parts cannot be tree-like but not every one of them should be)
- Integrate the Cobra into the game
- Weapons and ship equipment (basically a vector of stuff attached to a core, new core functionality of adding/removing equipment)
- Projectiles
- Clean up the "core" directory because it contains too many slightly unrelated files, probably needs splitting into subdirectories
- A factory for ships
- Randomly generate a bunch of backgrounds
- Convex Polygon Colliders (possibly using Separating Axis Theorem)
- Somehow make center of mass and the origin of the sprite separate
- Clean up the ship sprites since they are done in a band-aid currently
- Viable graphics
- Separate the drawing pipeline from physics, likely running them on two threads (which will be later useful for network play etc)

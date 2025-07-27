# spaceships
A simple game written in C++ using the SFML-3.0 library that I always wanted to make. Or at least make something similar.
# todo
- ShipSprite separate from ship
- Sprite manager
- Investigate the stupid framerate counter giving absurdly high values and slowly decreasing as game is running
- Fix the mess with spaceship cores and the remnants of the tree-like structure that was originaly intended for ship parts (not that parts cannot be tree-like but not every one of them should be)
- Change the way the menu draws sprites? (make it instead create a copy of the ship sprite and display it in the window)
- Integrate the Cobra into the game
- Camera adds center of mass to ship position when drawing (offset to the visual center of the sprite which is the origin?)
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

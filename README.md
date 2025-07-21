# spaceships
A simple game written in C++ using the SFML-3.0 library that I always wanted to make. Or at least make something similar.
# todo
- Different load commands for ship and background textures to avoid writing paths directly
- A factory for ships
- Do not translate symbolic units to screen pixels directly, rather implement a game camera
- Convex Polygon Colliders (possibly using Separating Axis Theorem)
- Somehow make center of mass and the origin of the sprite separate
- Clean up the ship sprites since they are done in a band-aid currently
- Viable graphics
- Separate the drawing pipeline from physics, likely running them on two threads (which will be later useful for network play etc)

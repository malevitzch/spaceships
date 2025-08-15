# spaceships
A simple game written in C++ using the SFML-3.0 library that I always wanted to make. Or at least make something similar.
# todo
## fixes
- CMake asset copying
- ProjectileSprite is literally a copy of ShipSprite (for now), they should probably have a common superclass that handles the shared behavior (rather than a literal Ctrl+C and Ctrl+V of the file with find and replace Ship -> Projectile)
- Consider using engine transforms in SimpleCore and OmniCore
- Battle should have its own file, not game.cpp
- Libraries are a bit too fragmented, too much unnecessary linking when they all depend on each other
- Clean up the "core" directory because it contains too many slightly unrelated files, probably needs splitting into subdirectories

## features
- Projectile sprite management
- Add some actual weapons or anything that can test the functionality of SimpleTriggerModule
- PhysicObject could have some nicer constructors
- Actually, a lot of the information could be kept in json
- Integrate the Cobra into the game
- Convex Polygon Colliders (possibly using Separating Axis Theorem)
- A factory for ships
- Separate the drawing pipeline from physics, likely running them on two threads (which will be later useful for network play etc)

## art and assets
- More elite bugships
- Rock ships
- Phase out the initial placeholder assets for ships such as bird, borg, and round
- Randomly generate a bunch of backgrounds

## other
- Update the introduction in the README (this document)
- Add some testing library

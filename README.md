# spaceships
A space combat game written in C++ using the SFML-3.0 library for graphics. Inspired by games such as Event Horizon and Reassembly.
# todo
## fixes
- Consider having weapon anchors not be a part of the weapon itself but rather be customizable
- Consider using engine transforms in SimpleCore and OmniCore
- Battle should have its own file, not game.cpp since game.cpp would eventually contain more things
- Libraries are a bit too fragmented, too much unnecessary linking when they all depend on each other
- Clean up the "core" directory because it contains too many slightly unrelated files, probably needs splitting into subdirectories

## features
- Ship buff / debuff system to allow applying things such as "angular velocity in a certain direction for X seconds"
- Ships created from json rather than by hand in code
- Extend json projectile types to allow for non-standard ones
- EnemyController
- PhysicsObject could have some nicer constructors
- Update weapon creation with a config struct so that it translates nicely to json
- Convex Polygon Colliders (possibly using Separating Axis Theorem)
- Separate the drawing pipeline from physics, likely running them on two threads (which will be later useful for network play etc)

## art and assets
- More elite bugships
- Rock ships
- Update Cobra and add it into the game
- Phase out the initial placeholder assets for ships such as bird, borg, and round
- Update backgrounds

## other
- Compound header for configs that can be included in factory
- PhysicsObject should have some convenient functions such as addAcceleration etc
- For the love of programming, shorten the utility/ directory to just util/ becuase this was a really dumb thing to do and I don't want to write the extra two letters every time
- Update the introduction in the README (this document)
- Add some testing library perhaps
- Extend logger with named variables that can be created and kept in a map so that certain things can be tracked in the background

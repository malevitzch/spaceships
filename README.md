# spaceships
A simple game written in C++ using the SFML-3.0 library that I always wanted to make. Or at least make something similar.
# todo
- Make ship sprites be tied to ShipActor and not SpaceshipCore
- Somehow make center of mass and the origin of the sprite separate
- Clean up the ship sprites since they are done in a band-aid currently
- Clean up SimpleCore and OmniCore draw()
- Finish implementing OmniCore by adding speed stabilization (with A + D the ship cancels out lateral movement and with W + S cancels main movement)
- Do not translate symbolic units to screen pixels directly, rather implement a game camera
- Viable graphics

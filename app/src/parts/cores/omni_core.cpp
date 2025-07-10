#include "parts/cores/omni_core.hpp"

namespace parts {

  OmniCore::OmniCore() : SpaceshipCore(100, 100) {
    if(!texture.loadFromFile("assets/graphics/OmniShip.png")) {
      throw new std::runtime_error("Failed to load texture for background");
    }
    sprite = std::make_shared<sf::Sprite>(sf::Sprite(texture));
    sprite->setOrigin({25, 25});
  }

  void OmniCore::physicsTick(double dt) {
    using util::Vec2d, util::Angle;

    // Those are not actualy X and Y axes
    // but rather the one parallel the ship direction
    // and the one perpendicular to it
    Vec2d ax = engines.x * Vec2d(thrust, getAngle());
    Vec2d ay = engines.y * Vec2d(thrust, getAngle() + std::numbers::pi / 2);
    transform.acceleration += ax + ay;

    double ang = angular_thrust * angular_engines;
    transform.angular_acceleration += ang;

    PhysicsObject::physicsTick(dt);

    transform.acceleration -= ax + ay;
    transform.angular_acceleration -= ang;
  }

  //FIXME: this could be implemented in SpaceshipCore
  void OmniCore::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(transform.position);
    states.transform.rotate(sf::radians(transform.angle));

    target.draw(*sprite, states);
  }

  void OmniCore::handleInstructions(controls::ShipOrders input) {
    int dy = input.right - input.left;
    int dx = input.ahead - input.back;

    setXEngine(dx);
    setYEngine(dy);

    int ang = input.right_arrow - input.left_arrow;
    setAngular(ang);
  }

  void OmniCore::setXEngine(int direction) {
    engines.x = direction;
  }

  void OmniCore::setYEngine(int direction) {
    engines.y = direction;
  }

  void OmniCore::setAngular(int direction) {
    angular_engines = direction;
  }
}

#include "parts/cores/simple_core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>

namespace parts {
  SimpleCore::SimpleCore() : SpaceshipCore(100, 100) {
    transform.position = {500, 500};
  }
  void SimpleCore::physicsTick(double dt) {
    // We first add the thrust to the transform (if engines are on),
    // then we compute the physics tick
    // And finally we subtract it back
    util::Vec2d acceleration = {0, 0};
    if(engines_on) {
      acceleration =
        {(float)(thrust * cos(transform.angle)), (float)(thrust * sin(transform.angle))};
    }

    transform.acceleration += acceleration;
    transform.angular_acceleration += angular_thrust * angular_engines;

    transform.tick(dt);

    transform.acceleration -= acceleration;
    transform.angular_acceleration -= angular_thrust * angular_engines;
  }
  void SimpleCore::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setOrigin({25, 25});
    shape.setPosition({(float)transform.position.x, (float)transform.position.y});
    shape.setRotation(sf::radians(transform.angle));
    
    sf::CircleShape circle(4);
    circle.setOrigin({4 - 21, 4});
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({(float)transform.position.x, (float)transform.position.y});
    circle.setRotation(sf::radians(transform.angle));

    target.draw(shape);
    target.draw(circle);
  }
  std::vector<std::shared_ptr<Part>> SimpleCore::getChildren() {
    return {};
  }
  void SimpleCore::handleInstructions(controls::PlayerInput input) {
    if(input.ahead) {
      turn_on_engines();
    } else {
      turn_off_engines();
    }
    // Pressing both buttons at once makes the ship try to stablize rotation
    if(input.left && input.right) {
      if(getAngularVelocity() > 0) {
        angular_left();
      } else if(getAngularVelocity() < 0) {
        angular_right();
      } else {
        angular_off();
      }
    } else if(input.left) {
      angular_left();
    } else if(input.right) {
      angular_right();
    } else {
      angular_off();
    }
  }

  void SimpleCore::turn_on_engines() {
    engines_on = true;
  }
  void SimpleCore::turn_off_engines() {
    engines_on = false;
  }

  void SimpleCore::angular_left() {
    angular_engines = -1;
  }
  void SimpleCore::angular_right() {
    angular_engines = 1;
  }
  void SimpleCore::angular_off() {
    angular_engines = 0;
  }

}

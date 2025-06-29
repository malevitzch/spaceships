#include "parts/cores/simple_core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>


namespace parts {
  SimpleCore::SimpleCore() : SpaceshipCore(100, 100) {
    transform.position = {500, 500};
  }
  void SimpleCore::physicsTick(double dt) {
    //FIXME: we always add the acceleration if the engines are live
    // when in reality it should only be added when it matters
    // We will do a band aid solution that just simply 
    // does not allow for other sources of acceleration
    if(engines_on) {
      util::Vec2d acceleration =
        {(float)(thrust * cos(transform.angle)), (float)(thrust * sin(transform.angle))};
      transform.acceleration = acceleration;
    } else {
      transform.acceleration = {0, 0};
    }

    transform.angular_acceleration = angular_thrust * angular_engines;

  transform.tick(dt);
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

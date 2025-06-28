#include "parts/cores/simple_core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>


namespace parts {
  SimpleCore::SimpleCore() : SpaceshipCore(100, 100) {
    // transform.acceleration = {0.01, 0.01};
    transform.angular_velocity = {0.001};
    transform.angular_acceleration = {0.001};
    transform.angle = 2;
    transform.position = {500, 500};
  }
  void SimpleCore::physicsTick(double dt) {
    double thrust = 0.00001;
    sf::Vector2f acceleration =
      {(float)(thrust * cos(transform.angle)), (float)(thrust * sin(transform.angle))};
    transform.acceleration.x += acceleration.x;
    transform.acceleration.y += acceleration.y;
    transform.tick(dt);
  }
  void SimpleCore::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setOrigin({25, 25});
    shape.setPosition({(float)transform.position.x, (float)transform.position.y});
    shape.setRotation(sf::radians(transform.angle));
    target.draw(shape);
  }
  std::vector<std::shared_ptr<Part>> SimpleCore::getChildren() {
    return {};
  }
}

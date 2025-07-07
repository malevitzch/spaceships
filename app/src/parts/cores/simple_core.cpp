#include "parts/cores/simple_core.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>

#include "physics/physics_object.hpp"
#include "utility/normalizer.hpp"

namespace parts {
  SimpleCore::SimpleCore() : SpaceshipCore(100, 100) {
    transform.position = {500, 500};
    if(!texture.loadFromFile("assets/graphics/BasicShip.png")) {
      throw new std::runtime_error("Failed to load texture for background");
    }

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

    PhysicsObject::physicsTick(dt);

    transform.acceleration -= acceleration;
    transform.angular_acceleration -= angular_thrust * angular_engines;
  }
  void SimpleCore::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    /*sf::RectangleShape shape;
    shape.setSize({50, 50});
    shape.setOrigin({25, 25});
    shape.setPosition({(float)transform.position.x, (float)transform.position.y});
    shape.setRotation(sf::radians(transform.angle));

    sf::CircleShape circle(4);
    circle.setOrigin({4 - 21, 4});
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({(float)transform.position.x, (float)transform.position.y});
    circle.setRotation(sf::radians(transform.angle));*/
    static sf::Sprite sprite(texture);
    sprite.setOrigin({25, 25});
    sprite.setPosition({(float)transform.position.x, (float)transform.position.y});
    sprite.setRotation(sf::radians(transform.angle));

    target.draw(sprite);
    /*target.draw(shape);
    target.draw(circle);*/
  }
  std::vector<std::shared_ptr<Part>> SimpleCore::getChildren() {
    return {};
  }
  void SimpleCore::handleInstructions(controls::ShipOrders input) {
    if(input.ahead) {
      turnOnEngines();
    } else {
      turnOffEngines();
    }
    // Pressing both buttons at once makes the ship try to stablize rotation
    if(input.left && input.right) {
      util::normalize(
        *this,
        static_cast<double (SimpleCore::*)() const>(&PhysicsObject::getAngularVelocity),
        &SimpleCore::angularRight,
        &SimpleCore::angularLeft,
        &SimpleCore::angularOff);
    } else if(input.left) {
      angularLeft();
    } else if(input.right) {
      angularRight();
    } else {
      angularOff();
    }
  }

  void SimpleCore::turnOnEngines() {
    engines_on = true;
  }
  void SimpleCore::turnOffEngines() {
    engines_on = false;
  }

  void SimpleCore::angularLeft() {
    angular_engines = -1;
  }
  void SimpleCore::angularRight() {
    angular_engines = 1;
  }
  void SimpleCore::angularOff() {
    angular_engines = 0;
  }

}

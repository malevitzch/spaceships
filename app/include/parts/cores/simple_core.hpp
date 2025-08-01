#ifndef SIMPLE_CORE_HPP
#define SIMPLE_CORE_HPP

#include "spaceship_core.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "controls/ship_orders.hpp"

#include "utility/normalizer.hpp"

namespace parts {
  class SimpleCore : public SpaceshipCore {
  private:
    double thrust = 8000;
    bool engines_on = false;

    double angular_thrust = 3;
    // left is -1 and right is 1
    int angular_engines = 0;

    std::shared_ptr<sf::Texture> texture;
  public:
    SimpleCore();
    SimpleCore(double thrust, double angular_thrust);

    virtual void physicsTick(double dt) override;
    virtual std::vector<std::shared_ptr<Part>> getChildren() override;

    virtual void handleInstructions(controls::ShipOrders input) override;

    void turnOnEngines();
    void turnOffEngines();

    void angularLeft();
    void angularRight();
    void angularOff();
  };
}

#endif

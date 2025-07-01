#ifndef SIMPLE_CORE_HPP
#define SIMPLE_CORE_HPP

#include "spaceship_core.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "controls/player_input.hpp"

namespace parts {
  class SimpleCore : public SpaceshipCore {
  private:
    double thrust = 7000;
    bool engines_on = false;

    double angular_thrust = 3;
    // left is -1 and right is 1
    int angular_engines = 0;
  public:
    SimpleCore();
    virtual void physicsTick(double dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual std::vector<std::shared_ptr<Part>> getChildren() override;

    virtual void handleInstructions(controls::PlayerInput input) override;

    void turn_on_engines();
    void turn_off_engines();

    void angular_left();
    void angular_right();
    void angular_off();
  };
}

#endif

#ifndef PARTS_CORES_OMNI_CORE_HPP
#define PARTS_CORES_OMNI_CORE_HPP

#include "spaceship_core.hpp"
#include "utility/vec2d.hpp"

namespace parts {
  // Short for OmnidirectionalCore
  class OmniCore : public SpaceshipCore {
  private:
    // TODO: thrust should perhaps not be locked like this
    double thrust = 7000;
    // First is forward/backward
    // Second is left/right
    // All relative to ship orientation
    util::Vec2d engines = {0, 0};

    double angular_thrust = 1;
    int angular_engines = 0;

    std::shared_ptr<sf::Texture> texture;
  public:
    OmniCore();
    virtual void physicsTick(double dt) override;
    virtual void draw(
      sf::RenderTarget& target,
      sf::RenderStates states) const override;

    virtual void handleInstructions(controls::ShipOrders input) override;

    void setXEngine(int direction);
    void engineXForward();
    void engineXBack();
    void engineXOff();

    void setYEngine(int direction);
    void engineYForward();
    void engineYBack();
    void engineYOff();

    void setAngular(int direction);
  };
}
#endif

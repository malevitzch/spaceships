#ifndef PARTS_CORES_OMNI_CORE_HPP
#define PARTS_CORES_OMNI_CORE_HPP

#include "ship_core.hpp"
#include "utility/vec2d.hpp"

namespace parts {
  // Short for OmnidirectionalCore
  class OmniCore : public ShipCore {
  private:
    double front_thrust = 0;
    double back_thrust = 0;
    double side_thrust = 0;
    // First is forward/backward
    // Second is left/right
    // All relative to ship orientation
    util::Vec2d engines = {0, 0};

    double angular_thrust = 1;
    double angular_engines = 0;

    bool dampener = true;

  public:
    OmniCore(double front_thrust, double back_thrust, double side_thrust);
    virtual void physicsTick(double dt) override;

    virtual void handleInstructions(controls::ShipOrders input) override;

    virtual void resetState() override;

    void setXEngine(double direction);
    void engineXForward();
    void engineXBack();
    void engineXOff();
    double getXEngineVelocity() const;

    void setYEngine(double direction);
    void engineYForward();
    void engineYBack();
    void engineYOff();
    double getYEngineVelocity() const;

    void setAngular(double direction);
    void angularLeft();
    void angularRight();
    void angularOff();
  };
}
#endif

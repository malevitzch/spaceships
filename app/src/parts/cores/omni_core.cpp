#include "parts/cores/omni_core.hpp"
#include "utility/normalizer.hpp"
#include "assets/texture_manager.hpp"


#include <functional>

namespace parts {

  OmniCore::OmniCore() : SpaceshipCore(100, 100) {}

  void OmniCore::physicsTick(double dt) {
    using util::Vec2d, util::Angle;

    // Those are not actualy X and Y axes
    // but rather the one parallel the ship direction
    // and the one perpendicular to it
    Vec2d ax = engines.x * Vec2d(thrust, getAngle());
    Vec2d ay = engines.y * Vec2d(thrust, getAngle() + util::degrees(90));
    transform.acceleration += ax + ay;

    double ang = angular_thrust * angular_engines;
    transform.angular_acceleration += ang;

    PhysicsObject::physicsTick(dt);

    transform.acceleration -= ax + ay;
    transform.angular_acceleration -= ang;
  }

  void OmniCore::handleInstructions(controls::ShipOrders input) {
    int dy = input.right - input.left;
    int dx = input.ahead - input.back;

    setXEngine(dx);
    setYEngine(dy);
    dampener = dampener ^ (input.space % 2);
    if(dampener) {
      if(!input.right && !input.left) {
        util::normalize(*this,
                        &OmniCore::getYEngineVelocity,
                        &OmniCore::engineYForward,
                        &OmniCore::engineYBack,
                        &OmniCore::engineYOff);
      }
      if(!input.ahead && !input.back) {
        util::normalize(*this,
                        &OmniCore::getXEngineVelocity,
                        &OmniCore::engineXForward,
                        &OmniCore::engineXBack,
                        &OmniCore::engineXOff);
      }
    }

    int ang = input.right_arrow - input.left_arrow;
    setAngular(ang);
  }

  void OmniCore::setXEngine(int direction) {
    engines.x = direction;
  }
  void OmniCore::engineXForward() {
    setXEngine(1);
  }
  void OmniCore::engineXBack() {
    setXEngine(-1);
  }
  void OmniCore::engineXOff() {
    setXEngine(0);
  }
  double OmniCore::getXEngineVelocity() const {
    util::Vec2d xengine_unit = util::Vec2d::unit(getAngle());
    return getVelocity().scalarProjection(xengine_unit);
  }

  void OmniCore::setYEngine(int direction) {
    engines.y = direction;
  }
  void OmniCore::engineYForward() {
    setYEngine(1);
  }
  void OmniCore::engineYBack() {
    setYEngine(-1);
  }
  void OmniCore::engineYOff() {
    setYEngine(0);
  }
  double OmniCore::getYEngineVelocity()const {
    util::Vec2d yengine_unit = util::Vec2d::unit(getAngle() + util::degrees(90));
    return getVelocity().scalarProjection(yengine_unit);
  }

  void OmniCore::setAngular(int direction) {
    angular_engines = direction;
  }
}

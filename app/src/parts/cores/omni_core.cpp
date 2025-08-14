#include "parts/cores/omni_core.hpp"
#include "utility/normalizer.hpp"

namespace parts {

  OmniCore::OmniCore(double front_thrust, double back_thrust, double side_thrust)
  :
  front_thrust(front_thrust),
  back_thrust(back_thrust),
  side_thrust(side_thrust) {}

  void OmniCore::physicsTick(double dt) {
    using util::Vec2d, util::Angle;

    // Those are not actualy X and Y axes
    // but rather the one parallel the ship direction
    // and the one perpendicular to it
    double xthrust = engines.x > 0 ? front_thrust : back_thrust;
    Vec2d ax = engines.x * Vec2d(xthrust, getAngle());
    Vec2d ay = engines.y * Vec2d(side_thrust, getAngle() + util::degrees(90));
    getTransform().acceleration += ax + ay;

    double ang = angular_thrust * angular_engines;
    getTransform().angular_acceleration += ang;

    PhysicsObject::physicsTick(dt);

    getTransform().acceleration -= ax + ay;
    getTransform().angular_acceleration -= ang;
  }

  void OmniCore::handleInstructions(controls::ShipOrders input) {
    int dy = input.right - input.left;
    int dx = input.ahead - input.back;

    setXEngine(dx);
    setYEngine(dy);

    double ang = input.right_arrow - input.left_arrow;
    setAngular(ang);

    dampener = dampener ^ (input.space_p % 2);
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
      if(!input.left_arrow && !input.right_arrow) {
        util::normalize(*this,
                        static_cast<double (OmniCore::*)() const>(
                          &PhysicsObject::getAngularVelocity),
                        &OmniCore::angularRight,
                        &OmniCore::angularLeft,
                        &OmniCore::angularOff);
      }
    }

  }

  void OmniCore::resetState() {
    ShipCore::resetState();
    engines = {0, 0};
    angular_engines = 0;
    dampener = true;
  }

  void OmniCore::setXEngine(double direction) {
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

  void OmniCore::setYEngine(double direction) {
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
  double OmniCore::getYEngineVelocity() const {
    util::Vec2d yengine_unit = util::Vec2d::unit(getAngle() + util::degrees(90));
    return getVelocity().scalarProjection(yengine_unit);
  }

  void OmniCore::setAngular(double direction) {
    angular_engines = direction;
  }
  void OmniCore::angularLeft() {
    angular_engines = -1;
  }
  void OmniCore::angularRight() {
    angular_engines = 1;
  }
  void OmniCore::angularOff() {
    angular_engines = 0;
  }
}

#ifndef PARTS_MODULES_SIMPLE_WEAPON_HPP
#define PARTS_MODULES_SIMPLE_WEAPON_HPP

#include "simple_trigger_module.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"

namespace parts {

  class SimpleWeapon : public SimpleTriggerModule {
  private:
  protected:
    util::Vec2d offset;
    util::Angle rotation;
    std::string projectile_sprite_name;
    double projectile_velocity;
    double projectile_duration;
    double spread;
  public:
    SimpleWeapon(int signal_code,
                 double cooldown,
                 std::string projectile_sprite_name,
                 util::Vec2d offset,
                 util::Angle rotation,
                 double projectile_velocity,
                 double projectile_duration,
                 double spread);
    virtual void trigger() override;
  };

}

#endif

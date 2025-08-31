#ifndef PARTS_MODULES_SIMPLE_WEAPON_HPP
#define PARTS_MODULES_SIMPLE_WEAPON_HPP

#include "simple_trigger_module.hpp"
#include "utility/angle.hpp"
#include "utility/vec2d.hpp"

#include "parts/modules/configs/simple_weapon_config.hpp"

namespace parts {

  class SimpleWeapon : public SimpleTriggerModule {
  private:
  protected:
    Anchor anchor;
    std::string name;
    std::vector<ProjectileConfig> projectiles;
  public:
    SimpleWeapon(int signal_code, SimpleWeaponConfig config);
    virtual void trigger() override;
  };

}

#endif

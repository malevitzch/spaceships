#ifndef PARTS_FACTORY_HPP
#define PARTS_FACTORY_HPP

#include <map>
#include "modules/configs/simple_weapon_config.hpp"
#include "parts/modules.hpp"
#include "parts/modules/centrifugal_slingshot.hpp"

namespace parts {
  class Factory {
  private:
    static std::map<std::string, SimpleWeaponConfig> simple_weapons;
  public:
    static void loadTriggerModules(std::vector<std::string> filenames);
    static void init(std::vector<std::string> filenames);
    // FIXME: this only supports simple weapons for now
    static std::shared_ptr<TriggerModule> getTriggerModule(std::string name,
                                                           int sig_code = -1);

    static std::shared_ptr<NullBrake> getNullBrake(int signal_code,
                                                   double cooldown,
                                                   double efficiency = 1.0,
                                                   double angular_efficiency = 1.0);

    static std::shared_ptr<VelocityRedirector> getVelocityRedirector(
      int signal_code,
      double cooldown,
      double efficiency = 1.0);

    static std::shared_ptr<CentrifugalSlingshot> getCentrifugalSlingshot(
      int signal_code,
      double cooldown,
      double multiplier = 50.0,
      double efficiency = 1.0);
  };
}

#endif

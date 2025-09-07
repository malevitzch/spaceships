#ifndef PARTS_FACTORY_HPP
#define PARTS_FACTORY_HPP

#include <map>
#include "modules/configs/simple_weapon_config.hpp"
#include "modules/trigger_module.hpp"

namespace parts {
  class Factory {
  private:
    static std::map<std::string, SimpleWeaponConfig> simple_weapons;
  public:
    static void loadTriggerModules(std::vector<std::string> filenames);
    static void init(std::vector<std::string> filenames);
    // FIXME: this only supports simple weapons for now
    static std::unique_ptr<TriggerModule> getTriggerModule(std::string name, int sig_code);
  };
}

#endif

#include "parts/factory.hpp"
#include "assets/paths.hpp"
#include "parts/modules/simple_weapon.hpp"
#include <fstream>

#include "logs/logger.hpp"


namespace parts {
  std::map<std::string, SimpleWeaponConfig> Factory::simple_weapons;

  void Factory::loadSimpleWeapons(std::vector<std::string> filenames) {
    // FIXME: it would probably make sense for the modules to just be in
    // mixed files where every module just contains type informations
    // that is later used to pick the correct constructor, that way we just
    // have a 'trigger_modules' map rather than this, but that's for later
    using nlohmann::json;
    std::string path = assets::paths::getAssetsPath() + "/json/";
    for(std::string filename : filenames) {
      // TODO: this should perhaps get logged somewhere
      // if we fail to open file or the json is faulty
      std::ifstream datastream(path + filename);
      json data = json::parse(datastream);
      for(json& weapon_data : data) {
        SimpleWeaponConfig config = SimpleWeaponConfig::fromJson(weapon_data);
        if(config.name == "___Anonymous___") {
          logs::Logger::logWarning(
            "Loading anonymous simple weapon (missing \"name\" field)");
          continue;
        }
        simple_weapons[config.name] = config;
      }
    }
  }

  void Factory::init(std::vector<std::string> filenames) {
    // FIXME: make this more flexible
    loadSimpleWeapons(filenames);
  }

  std::unique_ptr<TriggerModule> Factory::getTriggerModule(std::string name, int sig_code) {
    // FIXME: guard against nonexistent modules by returning a dummy
    // in case the wanted one is not there
    if(!simple_weapons.contains(name)) {
      logs::Logger::logError("Unknown module: \"" + name + "\"");
    }
    std::unique_ptr<TriggerModule> module =
      std::make_unique<SimpleWeapon>(sig_code, simple_weapons.at(name));
    return module;
  }
}

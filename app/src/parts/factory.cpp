#include "parts/factory.hpp"
#include "assets/paths.hpp"
#include "logs/logger.hpp"
#include "parts/modules/centrifugal_slingshot.hpp"

#include "parts/cores.hpp"

#include <fstream>

namespace parts {
  std::map<std::string, SimpleWeaponConfig> Factory::simple_weapons;

  void Factory::loadTriggerModules(std::vector<std::string> filenames) {

    using nlohmann::json;
    std::string path = assets::paths::getAssetsPath() + "/json/";
    for(std::string filename : filenames) {
      // TODO: this should perhaps get logged somewhere
      // if we fail to open file or the json is faulty
      std::ifstream datastream(path + filename);
      json data = json::parse(datastream);
      for(json& module_data : data) {
        if(!module_data.contains("type")) {
          logs::Logger::logError("Module missing type in file "
                                  "\"" + filename + "\"");
          continue;
        }
        if(module_data["type"] == "simpleweapon") {
          SimpleWeaponConfig config = SimpleWeaponConfig::fromJson(module_data);
          if(config.name == "___Anonymous___") {
            logs::Logger::logWarning(
              "Loading anonymous simple weapon from file"
              "\"" + filename + "\" "
              "(missing \"name\" field)");
            continue;
          }
          simple_weapons[config.name] = config;
        } else {
          logs::Logger::logError("Unknown module type \""
                                 + (std::string)module_data["type"] +
                                "\" in file \"" + filename + "\"");


        }
      }
    }
  }

  TriggerModule* Factory::getTriggerModuleFromJSON(nlohmann::json data) {
    // FIXME: this should correctly identify module type and proceed accordinaly
  }

  std::vector<TriggerModule*> Factory::getTriggerModulesFromJSON(nlohmann::json data) {
    std::vector<TriggerModule*> modules;
    for(nlohmann::json& module_data : data) {
      TriggerModule* module = getTriggerModuleFromJSON(module_data);
      if(module) modules.push_back(module);
    }
  }

  void Factory::init(std::vector<std::string> filenames) {
    // FIXME: make this more flexible
    loadTriggerModules(filenames);
  }

  ShipCore* Factory::getCoreFromJSON(nlohmann::json data) {
    // FIXME: return nullptr if this fails
    std::string core_type = data["type"];
    
    // TODO: do not require full initialization and use defaults instead
    // FIXME: warnings/errors on missing stuff
    if(core_type == "simple") {
      double thrust = data["thrust"];
      double angular_thrust = data["angular_thrust"];
      return new SimpleCore(thrust, angular_thrust);
    }
    else if(core_type == "mouse") {
      double thrust = data["thrust"];
      double angular_thrust = data["angular_thrust"];
      return new MouseCore(thrust, angular_thrust);
    }
    else if(core_type == "omni") {
      // FIXME: add angular thrust
      double front_thrust = data["front_thrust"];
      double back_thrust = data["back_thrust"];
      double side_thrust = data["side_thrust"];
      return new OmniCore(front_thrust, back_thrust, side_thrust);
    }
    else {
      return nullptr;
    }
  }
  // sig_code is often irrelavant so it's -1 by default in the declaration
  TriggerModule* Factory::getTriggerModule(std::string name, int sig_code) {
    if(simple_weapons.contains(name)) {
      TriggerModule* module =
        new SimpleWeapon(sig_code, simple_weapons.at(name));
      return module;
    }

    TriggerModule* dummy = new DummyTriggerModule();
    logs::Logger::logError("Unknown module \"" + name + "\"."
                           " A dummy will be used instead");
    return dummy;
  }
  NullBrake* Factory::getNullBrake(int signal_code,
                                   double cooldown,
                                   double efficiency,
                                   double angular_efficiency) {
    return new NullBrake(signal_code, cooldown, efficiency, angular_efficiency);
  }
  VelocityRedirector* Factory::getVelocityRedirector(
        int signal_code,
        double cooldown,
        double efficiency) {
    return new VelocityRedirector(signal_code, cooldown, efficiency);
  }
  CentrifugalSlingshot* Factory::getCentrifugalSlingshot(
        int signal_code,
        double cooldown,
        double multiplier,
        double efficiency) {
    return new CentrifugalSlingshot(signal_code, cooldown, multiplier, efficiency);
  }


}

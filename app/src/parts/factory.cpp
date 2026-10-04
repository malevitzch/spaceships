#include "parts/factory.hpp"
#include "assets/paths.hpp"
#include "logs/logger.hpp"
#include "parts/modules/centrifugal_slingshot.hpp"

#include "parts/cores.hpp" // IWYU pragma: keep

#include <fstream>

namespace parts {
  std::map<std::string, SimpleWeaponConfig> Factory::simple_weapons;
  void Factory::loadTriggerModule(std::string filename) {
    using nlohmann::json;

    std::ifstream datastream(filename);
    if(!datastream) {
      logs::Logger::logError("Couldn't open module file \"" + filename + "\"");
      return;
    }

    json data;
    try {
      data = json::parse(datastream);
    } catch(const json::parse_error& error) {
      logs::Logger::logError("Failed to parse module file \"" + filename
                             + "\": " + error.what());
      return;
    }

    if(!data.is_array()) {
      logs::Logger::logError("Expected an array of modules in file \""
                             + filename + "\"");
      return;
    }

    for(const json& module_data : data) {
      getTriggerModuleFromJSON(module_data, filename);
    }
  }
  void Factory::loadTriggerModules(std::vector<std::string> filenames) {
    std::string asset_path = assets::paths::getAssetsPath() + "/json/";
    for(std::string filename : filenames) {
      loadTriggerModule(asset_path + filename);
    }
  }

  bool Factory::getTriggerModuleFromJSON(
      nlohmann::json module_data, const std::string& source_filename) {
    if(!module_data.is_object()) {
      logs::Logger::logError("Expected a module object in file \""
                             + source_filename + "\"");
      return false;
    }

    if(!module_data.contains("type") || !module_data["type"].is_string()) {
      logs::Logger::logError("Module missing a string type in file \""
                             + source_filename + "\"");
      return false;
    }

    const std::string type = module_data["type"];
    if(type != "simpleweapon") {
      logs::Logger::logError("Unknown module type \"" + type
                             + "\" in file \"" + source_filename + "\"");
      return false;
    }

    SimpleWeaponConfig config;
    try {
      config = SimpleWeaponConfig::fromJson(module_data);
    } catch(const nlohmann::json::exception& error) {
      logs::Logger::logError("Invalid module in file \"" + source_filename
                             + "\": " + error.what());
      return false;
    }

    if(config.name == "___Anonymous___") {
      logs::Logger::logWarning("Skipping anonymous simple weapon in file \""
                               + source_filename + "\" (missing \"name\")");
      return false;
    }

    simple_weapons[config.name] = std::move(config);
    return true;
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

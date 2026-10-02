#include "assets/font_manager.hpp"
#include "assets/paths.hpp"
#include <filesystem>

#include "logs/logger.hpp"

namespace assets {
  std::unordered_map<
    std::string,
    std::shared_ptr<sf::Font>> FontManager::fonts;

  // There is only one font and it's hardcoded for now, maybe later
  // modding can be made possible by font config files
  const std::unordered_map<
    std::string,
    std::string> FontManager::font_paths = {
      {"orbitron", "orbitron/orbitron.ttf"}};

  void FontManager::loadFont(std::string name, std::string path) {
    auto font =
      std::make_shared<sf::Font>();

    if(!font->openFromFile(paths::getAssetsPath() + "/fonts/" + path)) {
      logs::Logger::logError("Failed to load font \"" + name + "\"");
    }

    fonts[name] = font;
  }

  void FontManager::init() {
    for(auto&[name, path] : font_paths) {
      loadFont(name, path);
    }
  }

  std::shared_ptr<sf::Font> FontManager::getFont(std::string name, std::string default_name) {

    if(!font_paths.contains(name)) {
      if(name != "orbitron") {
        logs::Logger::logError("Couldn't find font \"" + name + "\", defaulting to " + default_name);
        return getFont("orbitron");
      } else {
        logs::Logger::logError("Couldn't find font \"" + name + "\", aborting...");
        // TODO: exception handling?
        throw std::runtime_error("Couldn't find font \"" + name + "\"");
      }
    }

    return fonts[name];
  }

  void FontManager::reset() {
    fonts.clear();
  }
}

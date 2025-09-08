#include "assets/font_manager.hpp"
#include "assets/paths.hpp"
#include <filesystem>

#include "logs/logger.hpp"

namespace assets {
  std::unordered_map<
    std::string,
    std::weak_ptr<sf::Font>> FontManager::fonts;
  const std::unordered_map<
    std::string,
    std::string> FontManager::font_paths = {
      {"orbitron", "orbitron/orbitron.ttf"}};

  std::shared_ptr<sf::Font> FontManager::getFont(std::string name) {
    if(fonts.contains(name) && fonts[name].lock()) {
      return fonts[name].lock();
    }

    if(!font_paths.contains(name)) {
      logs::Logger::logError("Couldn't find font \"" + name + "\"");
      // FIXME: default font
    }

    auto font = 
      std::make_shared<sf::Font>();
    if(!font->openFromFile(paths::getAssetsPath() + "/fonts/" + font_paths.at(name))) {
      logs::Logger::logError("Failed to load font \"" + name + "\"");
      //FIXME: default font
    }

    fonts[name] = font;
    return font;
  }
}

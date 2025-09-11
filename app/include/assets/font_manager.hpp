#ifndef ASSETS_FONT_MANAGER_HPP
#define ASSETS_FONT_MANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace assets {
  class FontManager {
  private:
    static std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;
    static const std::unordered_map<std::string, std::string> font_paths;

    static void loadFont(std::string name, std::string path);
  public:
    static void init();
    static std::shared_ptr<sf::Font> getFont(std::string name);
  };
}

#endif

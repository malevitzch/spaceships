#ifndef ASSETS_SPRITE_MANAGER
#define ASSETS_SPRITE_MANAGER

#include "core/ship_sprite.hpp"
#include "utility/vec2d.hpp"
#include <map>

namespace assets {
  class SpriteManager {
    struct ShipSpriteInfo {
      std::string texture_name;
      util::Vec2d center_of_mass;
      util::Vec2d sprite_size;
      double scale;

      std::shared_ptr<core::ShipSprite> sprite = nullptr;

      std::shared_ptr<core::ShipSprite> get();
    };
  private:
    static std::map<std::string, ShipSpriteInfo> sprites;
  public:
    static std::shared_ptr<core::ShipSprite> getShipSprite(std::string name);
  };
}

#endif

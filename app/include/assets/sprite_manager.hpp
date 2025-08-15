#ifndef ASSETS_SPRITE_MANAGER
#define ASSETS_SPRITE_MANAGER

#include "assets/object_sprite.hpp"
#include "utility/vec2d.hpp"
#include <map>

namespace assets {
  class SpriteManager {
    struct SpriteInfo {
      std::string texture_name;
      util::Vec2d center_of_mass;
      util::Vec2d sprite_size;
      double scale;

      std::shared_ptr<core::ObjectSprite> sprite = nullptr;

      std::shared_ptr<core::ObjectSprite> get();
    };
  private:
    static std::map<std::string, SpriteInfo> ship_sprites;
    static std::map<std::string, SpriteInfo> projectile_sprites;
  public:
    static void init();

    static void loadShipSprites();
    static void loadProjectileSprites();
    static std::shared_ptr<core::ObjectSprite> getShipSprite(std::string name);
    static std::shared_ptr<core::ObjectSprite> getProjectileSprite(std::string name);
  };
}

#endif

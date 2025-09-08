#ifndef ASSETS_SPRITE_MANAGER
#define ASSETS_SPRITE_MANAGER

#include "assets/object_sprite.hpp"
#include "utility/vec2d.hpp"
#include <map>

namespace assets {
  class SpriteManager {
    enum class SpriteType {
      Ship,
      Projectile
    };
    struct SpriteInfo {
      std::string texture_name;
      util::Vec2d center_of_mass = {0, 0};
      util::Vec2d sprite_size;
      double scale = 1.0;
      SpriteType type;

      std::shared_ptr<ObjectSprite> sprite = nullptr;

      std::shared_ptr<ObjectSprite> get();
    };
  private:
    static std::map<std::string, SpriteInfo> ship_sprites;
    static std::map<std::string, SpriteInfo> projectile_sprites;
  public:
    static void init();

    static bool loadShipSprites(std::string filename);
    static bool loadProjectileSprites(std::string filename);
    static std::shared_ptr<ObjectSprite> getShipSprite(std::string name);
    static std::shared_ptr<ObjectSprite> getProjectileSprite(std::string name);
  };
}

#endif

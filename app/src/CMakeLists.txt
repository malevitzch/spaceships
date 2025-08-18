set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/assets")
set(ASSETS_TARGET_DIR "${CMAKE_BINARY_DIR}/assets")

set(PARTSLIB_SOURCES
  parts/signal.cpp

  parts/cores/ship_core.cpp
  parts/cores/simple_core.cpp
  parts/cores/omni_core.cpp
  parts/cores/mouse_core.cpp

  parts/modules/module.cpp
  parts/modules/trigger_module.cpp
  parts/modules/simple_trigger_module.cpp
  parts/modules/null_brake.cpp
  parts/modules/velocity_redirector.cpp
  parts/modules/simple_weapon.cpp
)

set(PHYSICSLIB_SOURCES
  physics/physics_transform.cpp
  physics/physics_object.cpp
  physics/colliders/collider.cpp
  physics/colliders/sphere_collider.cpp
)

set(UTILITYLIB_SOURCES
  utility/vec2d.cpp
  utility/angle.cpp
)

set(CONTROLSLIB_SOURCES
  controls/ship_orders.cpp
  controls/controllers/controller.cpp
  controls/controllers/player_controller.cpp
  controls/controllers/enemy_controller.cpp
)

set(CORELIB_SOURCES
  core/camera.cpp
  core/game.cpp
  core/menu.cpp
  core/ship.cpp
  core/ship_actor.cpp

  core/objects/space_object.cpp
  core/objects/simple_projectile.cpp
)

set(ASSETSLIB_SOURCES
  assets/font_manager.cpp
  assets/texture_manager.cpp
  assets/sprite_manager.cpp
  assets/paths.cpp
  assets/object_sprite.cpp
)

add_library(partslib ${PARTSLIB_SOURCES})
target_link_libraries(partslib PUBLIC SFML::Graphics)
target_link_libraries(partslib PUBLIC utilitylib)
target_link_libraries(partslib PUBLIC physicslib)
target_link_libraries(partslib PUBLIC corelib)

add_library(physicslib ${PHYSICSLIB_SOURCES})
target_link_libraries(physicslib PUBLIC SFML::Graphics)

add_library(utilitylib ${UTILITYLIB_SOURCES})
target_link_libraries(utilitylib PUBLIC SFML::Graphics)

add_library(controlslib ${CONTROLSLIB_SOURCES})
target_link_libraries(controlslib PUBLIC SFML::Graphics)
target_link_libraries(controlslib PUBLIC corelib)

add_library(corelib ${CORELIB_SOURCES})
target_link_libraries(corelib PUBLIC SFML::Graphics)
target_link_libraries(corelib PUBLIC partslib)
target_link_libraries(corelib PUBLIC controlslib)

add_library(assetslib ${ASSETSLIB_SOURCES})
target_link_libraries(assetslib PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(assetslib PUBLIC SFML::Graphics)
target_link_libraries(assetslib PUBLIC corelib)


add_executable(game main.cpp)
target_compile_features(game PRIVATE cxx_std_20)
target_link_libraries(game PRIVATE
  partslib
  physicslib
  utilitylib
  controlslib
  corelib
  assetslib
)

target_link_libraries(game PRIVATE SFML::Graphics)

add_custom_command(
  TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_SOURCE_DIR}"
    "${ASSETS_TARGET_DIR}"
  COMMENT "Copying assets"
)

add_custom_target(clean_assets
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ASSETS_TARGET_DIR}"
  COMMENT "Cleaning up assets"
)




add_custom_target(run
  COMMAND game
  DEPENDS game 
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

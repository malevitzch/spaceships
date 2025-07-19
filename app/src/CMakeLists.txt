set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/assets")
set(ASSETS_TARGET_DIR "${CMAKE_BINARY_DIR}/assets")

set(PARTSLIB_SOURCES
  parts/part.cpp
  parts/cores/spaceship_core.cpp
  parts/cores/simple_core.cpp
  parts/cores/omni_core.cpp
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
)

set(CORELIB_SOURCES
  core/game.cpp
  core/menu.cpp
  core/ship.cpp
  core/ship_actor.cpp
)

set(ASSETSLIB_SOURCES
  assets/texture_manager.cpp
)

add_library(partslib ${PARTSLIB_SOURCES})
target_link_libraries(partslib PUBLIC SFML::Graphics)

add_library(physicslib ${PHYSICSLIB_SOURCES})
target_link_libraries(physicslib PUBLIC SFML::Graphics)

add_library(utilitylib ${UTILITYLIB_SOURCES})
target_link_libraries(utilitylib PUBLIC SFML::Graphics)

add_library(controlslib ${CONTROLSLIB_SOURCES})
target_link_libraries(controlslib PUBLIC SFML::Graphics)

add_library(corelib ${CORELIB_SOURCES})
target_link_libraries(corelib PUBLIC SFML::Graphics)
target_link_libraries(corelib PRIVATE partslib)

add_library(assetslib ${ASSETSLIB_SOURCES})
target_link_libraries(assetslib PUBLIC SFML::Graphics)


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

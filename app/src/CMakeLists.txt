set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/assets")
set(ASSETS_TARGET_DIR "${CMAKE_BINARY_DIR}/assets")

set(SOURCES

  parts/part.cpp
  parts/cores/spaceship_core.cpp
  parts/cores/simple_core.cpp
  parts/cores/omni_core.cpp

  physics/physics_transform.cpp
  physics/physics_object.cpp

  utility/vec2d.cpp
  utility/angle.cpp

  controls/ship_orders.cpp
  controls/controllers/controller.cpp
  controls/controllers/player_controller.cpp

  core/game.cpp
  core/menu.cpp
)

add_executable(main main.cpp ${SOURCES})
target_compile_features(main PRIVATE cxx_std_20)

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_SOURCE_DIR}"
    "${ASSETS_TARGET_DIR}"
  COMMENT "Copying assets"
)

target_link_libraries(main PRIVATE SFML::Graphics)


add_custom_target(run
  COMMAND main
  DEPENDS main
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

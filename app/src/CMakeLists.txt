
set(SOURCES

  parts/part.cpp
  parts/cores/spaceship_core.cpp
  parts/cores/simple_core.cpp

  physics/physics_transform.cpp
  physics/physics_object.cpp

  utility/vec2d.cpp
  utility/angle.cpp
)

add_executable(main main.cpp ${SOURCES})
target_compile_features(main PRIVATE cxx_std_20)

target_link_libraries(main PRIVATE SFML::Graphics)

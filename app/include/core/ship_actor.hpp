#ifndef CORE_SHIP_ACTOR_HPP
#define CORE_SHIP_ACTOR_HPP

#include "controls/controllers/controller.hpp"
#include "parts/cores/spaceship_core.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace core {

  //FIXME: for now its pretty much a struct cause I don't want to write
  // all the necessary accessors
  class ShipActor : public sf::Drawable {
  private:
  protected:
  public:
    std::shared_ptr<parts::SpaceshipCore> core;
    std::shared_ptr<controls::Controller> controller;
    mutable sf::Sprite sprite;
    ShipActor(
      std::shared_ptr<parts::SpaceshipCore> core,
      std::shared_ptr<controls::Controller> controller, 
      std::string texture_name);

    void makeDecisions();
    void physicsTick(double dt);

    virtual void draw(
      sf::RenderTarget& target,
      sf::RenderStates states) const override;
  };
}

#endif

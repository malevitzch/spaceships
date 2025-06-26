#ifndef SIMPLE_CORE_HPP
#define SIMPLE_CORE_HPP

#include "spaceship_core.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace parts {
  class SimpleCore : public SpaceshipCore {
  private:
  public:
    SimpleCore();
    virtual void physicsTick(double dt) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual std::vector<std::shared_ptr<Part>> getChildren() override;
  };
}

#endif

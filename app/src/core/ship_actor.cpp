#include "core/ship_actor.hpp"
#include "assets/texture_manager.hpp"
#include "controls/ship_orders.hpp"

namespace core {
  ShipActor::ShipActor(
    std::shared_ptr<parts::SpaceshipCore> core,
    std::shared_ptr<controls::Controller> controller,
    std::string texture_name)
  :
    core(core),
    controller(controller),
    sprite(*assets::TextureManager::getTexture(texture_name)) {
    sprite.setOrigin({25, 25});
  }

  void ShipActor::makeDecisions() {
    controls::ShipOrders orders = controller->getOrders();
    core->handleInstructions(orders);
  }

  void ShipActor::physicsTick(double dt) {
    core->physicsTick(dt);
  }

  void ShipActor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //FIXME: this part is going to be replaced by calculation of on-screen
    // position out of the logical position that the ship holds
    states.transform.translate(core->getPosition());
    states.transform.rotate(sf::radians(core->getAngle()));

    target.draw(sprite, states);
  }
}

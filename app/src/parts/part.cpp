#include "parts/part.hpp"

namespace parts {

  int Part::getSubtreeHp() {
    long hp = getHp();
    for(const auto& part : getChildren()) {
      hp += part->getSubtreeHp();
    }
    return hp;
  }

  int Part::getSubtreeMass() {
    long mass = getMass();
    for(const auto& part : getChildren()) {
      mass += part->getSubtreeMass();
    }
    return mass;
  }

}

#ifndef PART_HPP
#define PART_HPP

#include <vector>
#include <memory>

namespace parts {
  class Part {
  private:
  public:
    virtual int getHp() = 0;
    virtual int getSubtreeHp();
    virtual int getMass() = 0;
    virtual int getSubtreeMass();

    virtual std::vector<std::shared_ptr<Part>> getChildren() = 0;
  };

}

#endif

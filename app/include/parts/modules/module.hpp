#ifndef PARTS_MODULES_MODULE_HPP
#define PARTS_MODULES_MODULE_HPP

namespace parts {

  // Forward declaration is necessary here
  // since those two are codependent
  class SpaceshipCore;

  class Module {
  private:
  protected:
    // This uses raw pointers since the core pointer should be valid
    // at all times
    SpaceshipCore* core;
  public:
    void setCore(SpaceshipCore& core);
  };

}

#endif

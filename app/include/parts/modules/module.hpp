#ifndef PARTS_MODULES_MODULE_HPP
#define PARTS_MODULES_MODULE_HPP

namespace parts {

  // Forward declaration is necessary here
  // since those two are codependent
  class SpaceshipCore;

  class Module {
  private:
    void setCore(SpaceshipCore& core);
  protected:
    // This uses raw pointers since the core pointer should be valid
    // at all times, if the core is destroyed then so is the module
    SpaceshipCore* core;
  public:


  friend class SpaceshipCore;
  };

}

#endif

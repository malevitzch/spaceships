#ifndef PARTS_MODULES_MODULE_HPP
#define PARTS_MODULES_MODULE_HPP

namespace parts {

  // Forward declaration is necessary here
  // since those two are codependent
  class ShipCore;

  class Module {
  private:
    void setCore(ShipCore& core);
  protected:
    // This uses raw pointers since the core pointer should be valid
    // at all times, if the core is destroyed then so is the module
    ShipCore* core;
    ShipCore& getCore() const;

    // FIXME: add a way to access the game context
  public:
    // The behavior of this depends on the module
    virtual void reset();


  friend class ShipCore;
  };

}

#endif

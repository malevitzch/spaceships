#include "parts/signal.hpp"

namespace parts {

  Signal::Signal(int code) : code(code) {}

  Signal::Signal(int code, std::vector<std::string> args) :
    code(code),
    args(args) {}
};

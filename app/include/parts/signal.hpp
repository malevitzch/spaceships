#ifndef PARTS_SIGNAL_HPP
#define PARTS_SIGNAL_HPP

#include <string>
#include <vector>
namespace parts {
  struct Signal {
    int code;
    std::vector<std::string> args;

    Signal() = default;
    Signal(int code);
    Signal(int code, std::vector<std::string> args);
  };
}

#endif

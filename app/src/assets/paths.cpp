#include "assets/paths.hpp"
#include <filesystem>
namespace assets {
  namespace paths {
    std::string getAssetsPath() {
      namespace fs = std::filesystem;
      static std::string assets_path =
        fs::read_symlink("/proc/self/exe")
          .parent_path().string() + "/../assets";
      return assets_path;
    }
  }
}

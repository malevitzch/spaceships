#include "assets/paths.hpp"
#include <filesystem>
namespace assets {
  namespace paths {
    std::string getAssetsPath() {
      namespace fs = std::filesystem;
      #ifdef _WIN32
          wchar_t buffer[MAX_PATH];
          DWORD len = GetModuleFileNameW(NULL, buffer, MAX_PATH);

          std::filesystem::path exePath(buffer);
          std::filesystem::path assets_path_win = exePath.parent_path() / ".." / "assets";

          std::string assets_path = 
            assets_path_win.lexically_normal().string();
      #else
        static std::string assets_path =
          fs::read_symlink("/proc/self/exe")
            .parent_path().string() + "/../assets";
      #endif
      return assets_path;
    }
  }
}

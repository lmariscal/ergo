#include <ergo/path.hh>

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include <algorithm>
#include <array>

namespace ergo {

  std::string get_binary_path() {
    std::array<char, 512> buffer;
    std::fill(buffer.begin(), buffer.end(), '\0');

#if defined(WIN32) || defined(_WIN32)
    GetModuleFileName(nullptr, buffer.data(), MAX_PATH);
#elif defined(__linux__)
    ssize_t count = readlink("/proc/self/exe", buffer.data(), buffer.size());
#endif

    std::string result = std::string(buffer.begin(), buffer.end());
    std::replace(result.begin(), result.end(), '\\', '/');

    return result;
  }

} // namespace ergo

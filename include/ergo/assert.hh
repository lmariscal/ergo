#pragma region head

#ifndef ERGO_ASSERT_HH
#define ERGO_ASSERT_HH

#if defined(ERGO_DEBUG)

#if defined(__linux__) || defined(__APPLE__)
#define ERGO_DEBUG_BREAK() raise(SIGTRAP)
#elif defined(_WIN32)
#define ERGO_DEBUG_BREAK() __debugbreak()
#endif // OS

#if __has_include("spdlog/spdlog.h")
#define ERGO_LOG_ERROR(...) spdlog::error(__VA_ARGS__);
#define ERGO_LOG_CURRENT_POSITION() \
  ERGO_LOG_ERROR("Assertion triggered at:\n\t{}:{}:{}", __FILE__, __FUNCTION__, __LINE__);
#else
#include <iostream>
inline void ERGO_LOG_ERROR() { }
template<typename First, typename... Rest>
inline void ERGO_LOG_ERROR(First &&first, Rest &&...rest) {
  std::cerr << std::forward<First>(first);
  ERGO_LOG_ERROR(std::forward<Rest>(rest)...);
}

#define ERGO_LOG_CURRENT_POSITION() \
  ERGO_LOG_ERROR("Assertion triggered at:\n\t", __FILE__, ":", __FUNCTION__, ":", __LINE__, "\n");
#endif // __has_include("spdlog/spdlog.h")

#define ERGO_ASSERT_MESSAGE(condition, ...) \
  {                                         \
    if (!(condition)) {                     \
      ERGO_LOG_CURRENT_POSITION();          \
      ERGO_LOG_ERROR(__VA_ARGS__);          \
      ERGO_DEBUG_BREAK();                   \
    }                                       \
  }

#define ERGO_ASSERT(condition)     \
  {                                \
    if (!(condition)) {            \
      ERGO_LOG_CURRENT_POSITION(); \
      ERGO_DEBUG_BREAK();          \
    }                              \
  }

#else

#define ERGO_ASSERT_MESSAGE(contition, ...)
#define ERGO_ASSERT(condition)

#endif // ERGO_DEBUG

#endif // ERGO_ASSERT_HH

#pragma endregion // head

#pragma region head

#ifndef ERGO_TYPES_HH
#define ERGO_TYPES_HH

#include <cstdint>
#include <signal.h>
#include <string>

namespace ergo {

  using i8 = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;

  using u8 = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  using f32 = float;
  using f64 = double;

  using uchar = unsigned char;

  using b8 = std::uint8_t;
  using b16 = std::uint16_t;
  using b32 = std::uint32_t;
  using b64 = std::uint64_t;

#ifndef M_PI
  constexpr f32 M_PI = 3.14159265358979323846;
#endif

} // namespace ergo

#if defined(ERGO_DEBUG)

#if defined(__linux__) || defined(__APPLE__)
#define ERGO_DEBUG_BREAK() raise(SIGTRAP)
#elif defined(_WIN32)
#define ERGO_DEBUG_BREAK() __debugbreak()
#endif

#define ERGO_ASSERT(validate, ...)                              \
  {                                                             \
    if (!validate) {                                            \
      log::error("{}:{}:{}", __FILE__, __FUNCTION__, __LINE__); \
      log::error(__VA_ARGS__);                                  \
      ERGO_DEBUG_BREAK();                                       \
    }                                                           \
  }

#else

#define ERGO_ASSERT(validate, ...)

#endif // ERGO_DEBUG

#endif // ERGO_TYPES_HH

#pragma endregion // head

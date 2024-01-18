#pragma once

#include <cstdint>
#include <filesystem>
#include <format>
#include <glad/glad.h>
#include <string_view>

#define __FILENAME__ std::filesystem::path(__FILE__).filename().string()

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using f32 = float;
using f64 = double;

[[maybe_unused]] inline static void
_loader_message_log(std::string_view msg, std::string_view file, int32 line) {
  std::puts(
      std::format("[MESSAGE] in {} at line {} - \"{}\" \n", file, line, msg)
          .c_str());
}
#define MSG_LOG(m) _loader_message_log(m, __FILENAME__, __LINE__)

[[maybe_unused]] inline static void
_loader_error_log(std::string_view msg, std::string_view file, int32 line) {
  std::puts(std::format("[ERROR] in {} at line {} - \"{}\" \n", file, line, msg)
                .c_str());
}
#define ERROR_LOG(m) _loader_error_log(m, __FILENAME__, __LINE__)

#define IS_VERBOSE 1

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
constexpr int kWindow_width{1280};
constexpr int kWindow_height{720};

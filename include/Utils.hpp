#pragma once

#include "glad/glad.h"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace fn {
auto CreateGlfwWindow() -> GLFWwindow *;
auto LoadOpenGLFunctions() -> void;
auto ProcessInput(GLFWwindow *target_window) -> void;
auto InitGlfwAndGlad() -> GLFWwindow *;
} // namespace fn

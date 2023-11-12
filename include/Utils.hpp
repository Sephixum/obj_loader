/**
 * @file Utils.hpp
 *
 * @brief Usefull functions in order to
 * reduce main function's code.
 * 
 */
#pragma once

#include "glad/glad.h"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace fn {
auto createGlfwWindow() -> GLFWwindow *;
auto loadOpenGLFunctions() -> void;
auto processInput(GLFWwindow *target_window) -> void;
auto initGlfwAndGlad() -> GLFWwindow *;
} // namespace fn

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
#include <cmath>
#include <glm/glm.hpp>
#include <stdexcept>

namespace fn {
auto createGlfwWindow() -> GLFWwindow *;
auto loadOpenGLFunctions() -> void;
auto processInput(GLFWwindow *target_window) noexcept -> void;
auto initGlfwAndGlad() noexcept -> GLFWwindow *;
auto getGlfwPosition() noexcept -> glm::vec3;
} // namespace fn

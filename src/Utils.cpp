#include "Utils.hpp"

#include <stb_image.h>

auto fn::createGlfwWindow() -> GLFWwindow * {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto new_window = glfwCreateWindow(kWindow_width, kWindow_height,
                                     "OpenGL practice", nullptr, nullptr);
  if (new_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("[GLFW] Failed to create window.");
  } else if (IS_VERBOSE) {
    std::puts("[GLFW] Window created with success.");
  }

  return new_window;
}

auto fn::loadOpenGLFunctions() -> void {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error(
        "[GLFW] OpenGL functions pointers failed to load.");
  } else {
    if (IS_VERBOSE) {
      std::puts("[GLFW] OpenGL function pointers loaded.");
    }
  }
}

auto fn::processInput(GLFWwindow *target_window) noexcept -> void {
  if (glfwGetKey(target_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(target_window, true);
  }
}

auto fn::initGlfwAndGlad() noexcept -> GLFWwindow * {
  auto window = fn::createGlfwWindow();
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  fn::loadOpenGLFunctions();

  glViewport(0, 0, kWindow_width, kWindow_height);
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport(0, 0, width, height);
      });

  glEnable(GL_DEPTH_TEST);
  stbi_set_flip_vertically_on_load(true);

  return window;
}

auto fn::getGlfwPosition() noexcept -> glm::vec3 {
  auto x = 7.0f * std::cos(static_cast<float>(glfwGetTime()));
  auto z = 7.0f * std::sin(static_cast<float>(glfwGetTime()));
  return glm::vec3(x, 4.0f, z);
}

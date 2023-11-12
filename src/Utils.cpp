#include "Utils.hpp"

auto fn::CreateGlfwWindow() -> GLFWwindow * {
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

auto fn::LoadOpenGLFunctions() -> void {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error(
        "[GLFW] OpenGL functions pointers failed to load.");
  } else {
    if (IS_VERBOSE) {
      std::puts("[GLFW] OpenGL function pointers loaded.");
    }
  }
}

auto fn::ProcessInput(GLFWwindow *target_window) -> void {
  if (glfwGetKey(target_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(target_window, true);
  }
}

auto fn::InitGlfwAndGlad() -> GLFWwindow * {
  auto window = fn::CreateGlfwWindow();
  glfwMakeContextCurrent(window);

  fn::LoadOpenGLFunctions();
  glViewport(0, 0, kWindow_width, kWindow_height);

  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport(0, 0, width, height);
      });

  glEnable(GL_DEPTH_TEST);

  return window;
}

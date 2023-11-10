#include "ShaderProgram.hpp"
#include "globals.hpp"

#include <format>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

auto CreateGlfwWindow() -> GLFWwindow * {
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

auto LoadOpenGLFunctions() -> void {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error(
        "[GLFW] OpenGL functions pointers failed to load.");
  } else {
    if (IS_VERBOSE) {
      std::puts("[GLFW] OpenGL function pointers loaded.");
    }
  }
}

auto ProcessInput(GLFWwindow *target_window) -> void {
  if (glfwGetKey(target_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(target_window, true);
  }
}

auto main() -> int {
  auto window = CreateGlfwWindow();
  glfwMakeContextCurrent(window);
  LoadOpenGLFunctions();
  glViewport(0, 0, kWindow_width, kWindow_height);
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport(0, 0, width, height);
      });

  ShaderProgram shader_program("resources/shaders/simple_cube_vertex.glsl",
                               "resources/shaders/simple_cube_fragment.glsl");
  shader_program.Activate();

  std::vector<GLfloat> vertices{
      -0.5f, -0.5f, 0.0f, //
      0.5f,  -0.5f, 0.0f, //
      0.0f,  0.5f,  0.0f  //
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    ProcessInput(window);

    glClearColor(200 / 255.f, 160 / 255.f, 100 / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    /*
     * this is where you render.
     */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  shader_program.Delete();

  glfwTerminate();
  return EXIT_SUCCESS;
}

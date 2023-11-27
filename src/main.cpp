#include "Camera.hpp"
#include "Model.hpp"
#include "Utils.hpp"
#include "globals.hpp"
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <format>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

auto main() -> int {
  auto window = fn::initGlfwAndGlad();

  stbi_set_flip_vertically_on_load(true);

  ShaderProgram model_shader(
      "resources/shaders/model_shaders/model_vertex.glsl",
      "resources/shaders/model_shaders/model_fragment.glsl");
  ShaderProgram light_cube_shader(
      "resources/shaders/light_shaders/light_vertex.glsl",
      "resources/shaders/light_shaders/light_fragment.glsl");

  Camera instace_camera(kWindow_width / static_cast<float>(kWindow_height),
                        glm::vec3(0.0f, 0.0f, 2.0f), window);
  instace_camera.setFarPlane(1000.f);

  Model back_pack("resources/models/backpack/backpack.obj");
  Model cube("resources/models/cube/Cube obj.obj");

  glClearColor(0 / 255.f, 0 / 255.f, 0 / 255.f, 1.f);
  while (!glfwWindowShouldClose(window)) {
    fn::processInput(window);

    instace_camera.update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /**
     * Draw, binding and unbindings of main cube.
     *
     */
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

    model_shader.activate();
    model_shader.setMat4("camera", instace_camera.getCameraMatrix());
    model_shader.setMat4("model", model);
    back_pack.draw(model_shader);

    float radius = 5;
    float x = radius * std::cos(glfwGetTime());
    float z = radius * std::sin(glfwGetTime());
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, 3.f, z));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

    light_cube_shader.activate();
    model_shader.setMat4("camera", instace_camera.getCameraMatrix());
    model_shader.setMat4("model", model);
    cube.draw(light_cube_shader);
    light_cube_shader.deActivate();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}

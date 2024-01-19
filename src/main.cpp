#include "Camera.hpp"
#include "Model.hpp"
#include "Utils.hpp"
#include "globals.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

auto main() -> int {
  auto window = fn::initGlfwAndGlad();

  ShaderProgram model_shader(
      "assets/shaders/model_shaders/model_vertex.glsl",
      "assets/shaders/model_shaders/model_fragment.glsl");
  ShaderProgram light_cube_shader(
      "assets/shaders/light_shaders/light_vertex.glsl",
      "assets/shaders/light_shaders/light_fragment.glsl");

  Camera instace_camera(kWindow_width / static_cast<float>(kWindow_height),
                        glm::vec3(0.0f, 0.0f, 2.0f), window);
  instace_camera.setFarPlane(1000.f);

  Model back_pack("assets/models/backpack/backpack.obj");
  Model cube("assets/models/cube/Cube obj.obj");
  // Model iron_man("resources/models/IronMan/IronMan.obj");
  // Model iron_man("resources/models/nigger/nigger.obj");

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
    // model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    model_shader.activate();
    model_shader.setMat4("camera", instace_camera.getCameraMatrix());
    model_shader.setMat4("model", model);
    model_shader.deActivate();
    back_pack.draw(model_shader);

    float radius = 5;
    float x = radius * std::cos(glfwGetTime());
    float z = radius * std::sin(glfwGetTime());
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, 3.f, z));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

    light_cube_shader.activate();
    light_cube_shader.setMat4("camera", instace_camera.getCameraMatrix());
    light_cube_shader.setMat4("model", model);
    light_cube_shader.deActivate();
    cube.draw(light_cube_shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}

#include "Camera.hpp"
#include "EBO.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "globals.hpp"

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

  std::vector<float> vertices{
      //    CROORDS     //  TEXCOORDS  //    NORMALS      //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,   //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, //
                                                          //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,     //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,     //
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,    //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //
                                                          //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,   //
                                                          //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,     //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,    //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,   //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,     //
                                                          //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //
                                                          //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     //
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,    //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f    //
  };

  std::vector<glm::vec3> cube_positions{
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -10.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5),
      glm::vec3(2.03f, -2.0f, -2.5f), glm::vec3(1.5f, .02f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)};

  ShaderProgram cube_shader(
      "resources/shaders/cube_shaders/cube_vertex.glsl",
      "resources/shaders/cube_shaders/cube_fragment.glsl");
  ShaderProgram light_cube_shader(
      "resources/shaders/light_shaders/light_vertex.glsl",
      "resources/shaders/light_shaders/light_fragment.glsl");

  VBO cube_vbo(vertices.size() * sizeof(vertices[0]), vertices.data());

  VAO cube_vao;
  cube_vao.linkVBO(cube_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
  cube_vao.linkVBO(cube_vbo, 1, 2, GL_FLOAT, 8 * sizeof(float),
                   3 * sizeof(float));
  cube_vao.linkVBO(cube_vbo, 2, 3, GL_FLOAT, 8 * sizeof(float),
                   5 * sizeof(float));

  VAO light_vao;
  light_vao.linkVBO(cube_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);

  Texture container_texture("resources/textures/container2.png", GL_TEXTURE_2D,
                            GL_TEXTURE0);
  Texture container_specular("resources/textures/container2_specular.png",
                             GL_TEXTURE_2D, GL_TEXTURE1);

  Camera instace_camera(kWindow_width / static_cast<float>(kWindow_height),
                        glm::vec3(0.0f, 0.0f, 2.0f), window);
  instace_camera.setFov(90.f);

  Material instance_material("material", std::move(container_texture),
                             std::move(container_specular), 25.0f);

  Light instance_light("light", glm::vec3(0.2f, 0.2f, 0.2f),
                       glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
                       glm::vec3(-0.2f, -1.0f, -0.3f));
  instance_light.setLinear(0.045f);
  instance_light.setQuadratic(0.0075f);

  glClearColor(0 / 255.f, 0 / 255.f, 0 / 255.f, 1.f);
  while (!glfwWindowShouldClose(window)) {
    fn::processInput(window);

    instace_camera.update();
    instance_light.setPosition(fn::getGlfwPosition());
    auto model_matrix = glm::mat4(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /**
     * Draw, binding and unbindings of main cube.
     *
     */
    cube_shader.activate();
    cube_shader.setMat4("camera_matrix", instace_camera.getCameraMatrix());
    cube_shader.setVec3("camera_position", instace_camera.getCameraPosition());
    cube_shader.setMaterial(instance_material.getUniformName().c_str(),
                            instance_material);
    cube_shader.setLight(instance_light.getUniformName().c_str(),
                         instance_light);
    cube_vao.bind();
    for (unsigned int i = 0; i < cube_positions.size(); ++i) {
      model_matrix = glm::mat4(1.0f);
      model_matrix = glm::translate(model_matrix, cube_positions[i]);
      float angle = 20.0f * i;
      model_matrix = glm::rotate(model_matrix, glm::radians(angle),
                                 glm::vec3(1.0f, 0.3f, 0.5f));
      cube_shader.setMat4("model_matrix", model_matrix);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    cube_vao.unBind();
    ShaderProgram::deActivate();

    /**
     * Reseting model_matrix and preparing it for
     * the light_cube.
     *
     */
    model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, instance_light.getPosition());

    light_cube_shader.activate();
    light_cube_shader.setMat4("model_matrix", model_matrix);
    light_cube_shader.setMat4("camera_matrix",
                              instace_camera.getCameraMatrix());
    light_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  cube_vao.deleteArray();
  cube_vbo.deleteBuffer();
  cube_shader.deleteShader();

  glfwTerminate();
  return EXIT_SUCCESS;
}

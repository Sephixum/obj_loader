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
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
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

  ShaderProgram cube_shader(
      "resources/shaders/cube_shaders/cube_vertex.glsl",
      "resources/shaders/cube_shaders/cube_fragment.glsl");

  ShaderProgram light_cube_shader(
      "resources/shaders/light_shaders/light_vertex.glsl",
      "resources/shaders/light_shaders/light_fragment.glsl");

  VBO cube_vbo(vertices.size() * sizeof(vertices[0]), vertices.data());

  VAO cube_vao;
  cube_vao.linkVBO(cube_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
  cube_vao.linkVBO(cube_vbo, 1, 2, GL_FLOAT, 8 * sizeof(float),
                   (void *)(3 * sizeof(float)));
  cube_vao.linkVBO(cube_vbo, 2, 3, GL_FLOAT, 8 * sizeof(float),
                   (void *)(5 * sizeof(float)));

  VAO light_vao;
  light_vao.linkVBO(cube_vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);

  Texture red_bricks("resources/textures/red_bricks.png", GL_TEXTURE_2D, 0,
                     GL_UNSIGNED_BYTE);
  red_bricks.activate();
  red_bricks.bind();
  cube_shader.setTextureUnit("tex0", red_bricks.getTextureUnit());

  Camera instace_camera(kWindow_width / static_cast<float>(kWindow_height),
                        glm::vec3(0.0f, 0.0f, 2.0f), window);
  instace_camera.setFov(90.f);

  auto light_color = glm::vec3(1.0f, 1.0f, 1.0f);
  auto cube_color = glm::vec3(1.0f, 0.5f, 0.31f);

  auto circular_position = []() -> glm::vec3 {
    auto x = 7.0f * std::cos(static_cast<float>(glfwGetTime()));
    auto z = 7.0f * std::sin(static_cast<float>(glfwGetTime()));
    return glm::vec3(x, 4.0f, z);
  };

  Material instance_material("material", glm::vec3(1.0f, 0.5f, 0.31f),
                             glm::vec3(1.0f, 0.5f, 0.31f),
                             glm::vec3(0.5f, 0.5f, 0.5f), 128.0f);

  Light instance_light("light", glm::vec3(0.2f, 0.2f, 0.2f),
                       glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f),
                       circular_position());

  glClearColor(0 / 255.f, 0 / 255.f, 0 / 255.f, 1.f);
  while (!glfwWindowShouldClose(window)) {
    fn::processInput(window);

    instace_camera.update();

    auto model_matrix = glm::mat4(1.0f);

    instance_light.setPosition(circular_position());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /**
     * Draw, binding and unbindings of main cube.
     *
     */
    cube_shader.activate();
    cube_shader.setMat4("model_matrix", model_matrix);
    cube_shader.setMat4("camera_matrix", instace_camera.getCameraMatrix());
    cube_shader.setVec3("camera_position", instace_camera.getCameraPosition());
    cube_shader.setMaterial(instance_material.getUniformName().c_str(),
                            instance_material);
    cube_shader.setLight(instance_light.getUniformName().c_str(),
                         instance_light);
    cube_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    cube_vao.unBind();
    ShaderProgram::deActivate();

    /**
     * Reseting model_matrix and preparing it for
     * the light_cube.
     *
     */
    model_matrix = glm::mat4(0.1f);
    model_matrix = glm::scale(model_matrix, glm::vec3(0.3f, 0.3f, 0.3f));
    model_matrix = glm::translate(model_matrix, instance_light.getPosition());
    model_matrix = glm::rotate(model_matrix, (float)glfwGetTime(),
                               glm::vec3(1.0f, 1.0f, 1.0f));

    /**
     * Draw, Binding and unbindings of light_cube.
     *
     */
    light_cube_shader.activate();
    light_cube_shader.setMat4("model_matrix", model_matrix);
    light_cube_shader.setMat4("camera_matrix",
                              instace_camera.getCameraMatrix());
    light_cube_shader.setVec3("light_color", light_color);
    light_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    light_vao.unBind();
    ShaderProgram::deActivate();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  cube_vao.deleteArray();
  cube_vbo.deleteBuffer();
  cube_shader.deleteShader();
  red_bricks.deleteTexture();

  glfwTerminate();
  return EXIT_SUCCESS;
}

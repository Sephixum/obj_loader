#include "Camera.hpp"
#include "EBO.hpp"
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
#include <glm/vec3.hpp>
#include <stdexcept>
#include <vector>

auto main() -> int {
  auto window = fn::InitGlfwAndGlad();

  std::vector<float> vertices{
      //    CROORDS     //  TEXCOORDS //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
                                       //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
                                       //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   //
                                       //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
                                       //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   //
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  //
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
                                       //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  //
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    //
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   //
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f   //

  };
  // std::vector<unsigned int> indices{
  //     0, 1, 3, //
  //     1, 2, 3  //
  // };

  ShaderProgram shader_program("resources/shaders/simple_cube_vertex.glsl",
                               "resources/shaders/simple_cube_fragment.glsl");
  shader_program.Activate();

  VAO instance_vao;

  VBO square_vbo(vertices.size() * sizeof(vertices[0]), vertices.data());
  instance_vao.LinkVBO(square_vbo, 0, 3, GL_FLOAT, 5 * sizeof(float),
                       (void *)0);
  instance_vao.LinkVBO(square_vbo, 1, 2, GL_FLOAT, 5 * sizeof(float),
                       (void *)(3 * sizeof(float)));
  instance_vao.Bind();

  // EBO instance_ebo(indices.size() * sizeof(indices[0]), indices.data());
  // instance_ebo.Bind();

  Texture red_bricks("resources/textures/red_bricks.png", GL_TEXTURE_2D, 0,
                     GL_UNSIGNED_BYTE);
  red_bricks.Activate();
  red_bricks.Bind();
  shader_program.SetTextureUnit("tex0", red_bricks.GetTextureUnit());

  Camera instace_camera(kWindow_width / static_cast<float>(kWindow_height),
                        glm::vec3(0.0f, 0.0f, 2.0f));
  instace_camera.UpdateCameraMatrix(90.f, 0.1f, 100.f);
  instace_camera.SetCameraMatrixToShader(shader_program, "camera_matrix");

  glClearColor(150 / 255.f, 100 / 255.f, 120 / 255.f, 1.f);
  while (!glfwWindowShouldClose(window)) {
    fn::ProcessInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * this is where you render.
     */
    auto model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
    model_matrix = glm::rotate(model_matrix, (float)glfwGetTime(),
                               glm::vec3(0.25f, 3.0f, 1.0f));
    shader_program.SetMat4("model_matrix", model_matrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  instance_vao.Delete();
  square_vbo.Delete();
  shader_program.Delete();
  red_bricks.Delete();

  glfwTerminate();
  return EXIT_SUCCESS;
}

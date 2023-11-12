#include "EBO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

#include <GLFW/glfw3.h>
#include <format>
#include <glad/glad.h>
#include <stdexcept>
#include <vector>

auto main() -> int {
  GLFWwindow *window = fn::InitGlfwAndGlad();

  std::vector<float> vertices{
      //    CROORDS     //  TEXCOORDS //
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, //
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  //
  };
  std::vector<unsigned int> indices{
      0, 1, 3, //
      1, 2, 3  //
  };

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

  EBO instance_ebo(indices.size() * sizeof(indices[0]), indices.data());
  instance_ebo.Bind();

  Texture red_bricks("resources/textures/red_bricks.png", GL_TEXTURE_2D, 0,
                     GL_UNSIGNED_BYTE);
  red_bricks.Activate();
  red_bricks.Bind();

  shader_program.SetTextureUnit("tex0", red_bricks.GetTextureUnit());

  glClearColor(150 / 255.f, 100 / 255.f, 120 / 255.f, 1.f);
  while (!glfwWindowShouldClose(window)) {
    fn::ProcessInput(window);

    glClear(GL_COLOR_BUFFER_BIT);

    /*
     * this is where you render.
     */
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  instance_vao.Delete();
  square_vbo.Delete();
  shader_program.Delete();
  glfwTerminate();

  return EXIT_SUCCESS;
}

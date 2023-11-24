#pragma once

#include "EBO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VAO.hpp"

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

class Mesh {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<Texture> textures);
  auto draw(ShaderProgram &shader) -> void;

private:
  VAO vao_;
  VBO vbo_;
  EBO ebo_;
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  std::vector<Texture> textures_;


  auto setupMesh() -> void;
};

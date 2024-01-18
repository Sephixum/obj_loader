#pragma once

#include "EBO.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include <Vertex.hpp>

#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  Mesh(Vertices vertices, Indices indices, std::vector<Texture> textures);
  auto draw(ShaderProgram &shader) -> void;

private:
  auto setupMesh_() -> void;

  VAO vao_;
  VBO vbo_;
  EBO ebo_;
  Vertices vertices_;
  Indices indices_;
  std::vector<Texture> textures_;
};

using Meshes = std::vector<Mesh>;

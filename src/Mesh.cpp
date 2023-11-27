#include "Mesh.hpp"
#include <cstddef>
#include <string>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture> textures)
    : vertices_(vertices), indices_(indices), textures_(std::move(textures)) {
  setupMesh();
}

auto Mesh::draw(ShaderProgram &shader) -> void {
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for (unsigned int i = 0; i < textures_.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);

    std::string unit_number;
    std::string texture_type = textures_[i].type;
    if (texture_type == "texture_diffuse") {
      unit_number = std::to_string(++diffuseNr);
    } else if (texture_type == "texture_specular") {
      unit_number = std::to_string(++specularNr);
    }

    shader.setTextureUnit(("material." + texture_type + unit_number).c_str(),
                          i);
    glBindTexture(GL_TEXTURE_2D, textures_[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  // Draw mesh
  vao_.bind();
  ebo_.bind();
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
  ebo_.unBind();
  vao_.unBind();
}

auto Mesh::setupMesh() -> void {
  vao_.bind();

  vbo_.setBufferData(vertices_.size() * sizeof(Vertex), vertices_.data());
  ebo_.setBufferData(indices_.size() * sizeof(unsigned int), indices_.data());

  // Vertex positions
  vao_.linkVBO(vbo_, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
  // Vertex normals
  vao_.linkVBO(vbo_, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, Normal));
  // Vertex texture coords
  vao_.linkVBO(vbo_, 2, 2, GL_FLOAT, sizeof(Vertex),
               offsetof(Vertex, TexCoords));

  vao_.unBind();
}

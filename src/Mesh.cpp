#include "Mesh.hpp"

#include <iostream>
#include <string>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture> textures)
    : vertices_(vertices), indices_(indices), textures_(std::move(textures)) {
  setupMesh();
}

auto Mesh::draw(ShaderProgram &shader) -> void {
  unsigned int diffuseNr = 0;
  unsigned int specularNr = 0;
  for (unsigned int i = 0; i < textures_.size(); ++i) {

    std::string unit_number;
    std::string texture_type = textures_[i].getType();
    if (texture_type == "diffuse") {
      unit_number = std::to_string(++diffuseNr);
    } else if (texture_type == "specular") {
      unit_number = std::to_string(++specularNr);
    }

    shader.setTextureUnit((texture_type + unit_number).c_str(), i);
    textures_[i].activate(GL_TEXTURE0 + i);
    textures_[i].bind();
  }

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
  vao_.linkVBO(vbo_, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
  // Vertex colors
  vao_.linkVBO(vbo_, 2, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
  // Vertex texture coords
  vao_.linkVBO(vbo_, 3, 2, GL_FLOAT, sizeof(Vertex),
               offsetof(Vertex, tex_coords));

  vao_.unBind();
}

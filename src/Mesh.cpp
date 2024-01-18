#include "Mesh.hpp"
#include "Texture.hpp"
#include <Vertex.hpp>

#include <string>

Mesh::Mesh(Vertices vertices, Indices indices, std::vector<Texture> textures)
    : vertices_(vertices), indices_(indices), textures_(std::move(textures)) {
  setupMesh_();
}

auto Mesh::draw(ShaderProgram &shader) -> void {
  uint diffuseNr = 0;
  uint specularNr = 0;
  for (uint i = 0; i < textures_.size(); ++i) {

    std::string unit_number;
    std::string texture_type = textures_[i].getType();
    if (texture_type == "diffuse") {
      unit_number = std::to_string(++diffuseNr);
    } else if (texture_type == "specular") {
      unit_number = std::to_string(++specularNr);
    }

    shader.setTextureUnit((texture_type + unit_number).c_str(), i);
    textures_[i].bind(GL_TEXTURE0 + i);
  }

  vao_.bind();
  ebo_.bind();

  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);

  ebo_.unBind();
  vao_.unBind();
}

auto Mesh::setupMesh_() -> void {
  vao_.bind();

  vbo_.setBufferData(vertices_);
  ebo_.setBufferData(indices_);

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

#pragma once

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

#include <assimp/scene.h>
#include <iostream>
#include <string>
#include <vector>

class Model {
private:
  std::vector<Mesh> meshes_;
  std::vector<Texture> loaded_textures_;
  std::string directory_;

  auto loadTexture_(const char *path, const char *directory) -> GLuint;

public:
  Model(const char *path);
  auto draw(ShaderProgram &shader) -> void;
  auto loadModel(std::string path) -> void;
  auto processNode(aiNode *node, const aiScene *scene) -> void;
  auto processMesh(aiMesh *mesh, const aiScene *scene) -> Mesh;
  auto loadMaterialTextures(aiMaterial *material, aiTextureType type,
                            std::string type_name) -> std::vector<Texture>;
};

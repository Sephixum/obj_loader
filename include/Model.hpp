#pragma once

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

#include <assimp/scene.h>
#include <string>
#include <vector>

class Model {
private:
  Meshes meshes_;
  std::vector<Texture> loaded_textures_;
  std::string directory_;

public:
  Model(const char *path);
  auto draw(ShaderProgram &shader) -> void;
  auto loadModel(std::string path) -> void;
  auto processNode(aiNode *node, const aiScene *scene) -> void;
  auto processMesh(aiMesh *mesh, const aiScene *scene) -> Mesh;
  auto loadMaterialTextures(aiMaterial *material, aiTextureType type,
                            std::string type_name) -> std::vector<Texture>;
};

#include "Model.hpp"
#include "globals.hpp"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <format>

Model::Model(const char *path) { loadModel(path); }

auto Model::draw(ShaderProgram &shader) -> void {
  shader.activate();
  for (unsigned int i = 0; i < meshes_.size(); ++i) {
    meshes_[i].draw(shader);
  }
  shader.deActivate();
}

auto Model::loadModel(std::string path) -> void {
  Assimp::Importer importer;
  const aiScene *scene =
      importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    ERROR_LOG(std::format("[ASSIMP] {}", importer.GetErrorString()));
    return;
  }
  std::filesystem::path filesystem_path = path;
  directory_ = filesystem_path.remove_filename().string();
  processNode(scene->mRootNode, scene);
}

auto Model::processNode(aiNode *node, const aiScene *scene) -> void {
  for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(processMesh(mesh, scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i) {
    processNode(node->mChildren[i], scene);
  }
}

auto Model::processMesh(aiMesh *mesh, const aiScene *scene) -> Mesh {
  Vertices vertices;
  Indices indices;
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;

    // Process vertex positions
    auto position = mesh->mVertices[i];
    vertex.position = glm::vec3(position.x, position.y, position.z);

    // Process vertex normals
    if (mesh->HasNormals()) {
      auto normal = mesh->mNormals[i];
      vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
    }

    // Process vertex color
    if (mesh->HasVertexColors(0)) {
      auto color = mesh->mColors[i];
      vertex.color = glm::vec3(color->r, color->g, color->b);
    } else {
      vertex.color = glm::vec3(0.5f, 0.5f, 0.5f);
    }

    // Process vertex TexCoords
    if (mesh->HasTextureCoords(0)) {
      vertex.tex_coords =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    } else {
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  // Process indices
  for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
    auto face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; ++j) {
      indices.push_back(face.mIndices[j]);
    }
  }

  // Process material
  if (mesh->mMaterialIndex > 0) {
    auto material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuse_maps =
        loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
    for (const auto &t : diffuse_maps) {
      textures.push_back(std::move(t));
    }

    std::vector<Texture> specular_maps =
        loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
    for (const auto &t : specular_maps) {
      textures.push_back(std::move(t));
    }
  }

  return Mesh(vertices, indices, std::move(textures));
}

auto Model::loadMaterialTextures(aiMaterial *material, aiTextureType type,
                                 std::string type_name)
    -> std::vector<Texture> {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < material->GetTextureCount(type); ++i) {
    aiString str;
    material->GetTexture(type, i, &str);
    bool skip = false;
    for (unsigned int j = 0; j < loaded_textures_.size(); ++j) {
      if (loaded_textures_[j].getFileName() == str.C_Str()) {
        textures.push_back(loaded_textures_[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      std::string full_path = directory_ + std::string(str.C_Str());
      Texture texture(full_path, type_name);
      textures.push_back(texture);
      loaded_textures_.push_back(texture);
      MSG_LOG(std::format("texture {} id {} loaded.",
                          texture.getFileName(), texture.getId()));
    }
  }
  return textures;
}

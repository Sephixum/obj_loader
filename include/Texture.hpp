/**
 * @file Texture.hpp
 *
 * @brief This class controlls binding, unbinding and
 * id for a texture object.
 *
 */
#pragma once

#include <format>
#include <glad/glad.h>
#include <string>

class Texture {
private:
  GLuint id_;
  std::string type_;
  std::string file_name_;

public:
  Texture(std::string image_path, std::string type_name);

  auto bind() const noexcept -> void;
  static auto unBind() noexcept -> void;
  auto activate(GLenum slot) const noexcept -> void;

  auto setType(std::string_view new_type) noexcept -> void;
  auto setFileName(std::string_view new_file_name) noexcept -> void;

  auto getType() const noexcept -> std::string;
  auto getFileName() const noexcept -> std::string;
  auto getId() const noexcept -> GLuint;
};

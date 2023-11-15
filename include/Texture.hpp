/**
 * @file Texture.hpp
 *
 * @brief This class controlls binding, unbinding and
 * id for a texture object.
 *
 */
#pragma once

#include "globals.hpp"

#include <format>
#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>

using uint = unsigned int;

class Texture {
private:
  auto checkFirstInstantiation_() const noexcept -> void;

  uint id_;
  uint texture_type_;
  uint texture_unit_;

  static bool is_first_instance_;

public:
  explicit Texture() = default;
  explicit Texture(const char *image_path, uint texture_type, uint slot);

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteTexture() const noexcept -> void;

  [[nodiscard]] auto getTextureUnit() const noexcept -> uint;
  [[nodiscard]] auto getId() const noexcept -> uint;
};

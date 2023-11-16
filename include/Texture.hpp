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
#include <math.h>
#include <stb_image.h>
#include <stdexcept>

class Texture {
private:
  auto checkFirstInstantiation_() const noexcept -> void;

  unsigned int id_;
  unsigned int texture_type_;
  unsigned int texture_unit_;

  static bool is_first_instance_;

public:
  explicit Texture() = default;
  explicit Texture(const char *image_path, unsigned int texture_type,
                   unsigned int slot);
  explicit Texture(const Texture &other);

  auto operator=(const Texture &rhs) -> Texture &;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteTexture() const noexcept -> void;

  [[nodiscard]] auto getId() const noexcept -> unsigned int;
  [[nodiscard]] auto getTextureUnit() const noexcept -> unsigned int;
};

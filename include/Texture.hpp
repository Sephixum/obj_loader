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

  GLuint id_;
  GLenum texture_type_;
  GLenum texture_slot_;

  static bool is_first_instance_;

public:
  Texture(const char *image_path, GLenum texture_type, GLenum slot);
  Texture(const Texture &other) = default;
  auto operator=(const Texture &rhs) -> Texture & = default;
  Texture(Texture &&other) = default;
  auto operator=(Texture &&rhs) -> Texture & = default;
  ~Texture();

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;

  [[nodiscard]] auto getId() const noexcept -> unsigned int;
  [[nodiscard]] auto getTextureSlot() const noexcept -> unsigned int;
};

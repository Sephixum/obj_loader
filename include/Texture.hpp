#pragma once

#include "stb_image.h"

#include <format>
#include <glad/glad.h>
#include <stdexcept>

using uint = unsigned int;

class Texture {
private:
  uint id_;
  uint texture_type_;
  uint texture_unit_;

  inline static bool is_first_instance_{true};

public:
  explicit Texture() = default;
  explicit Texture(const char *image_path, uint texture_type, uint slot,
                   uint pixel_type);

  auto Bind() const noexcept -> void;
  auto UnBind() const noexcept -> void;
  auto Activate() const noexcept -> void;
  auto DeActivate() const noexcept -> void;
  auto Delete() const noexcept -> void;
  auto GetTextureUnit() const noexcept -> uint;

  auto CheckFirstInstantiation() const noexcept -> void;
};

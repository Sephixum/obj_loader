#pragma once

#include "stb_image.h"

#include <format>
#include <glad/glad.h>
#include <stdexcept>

using uint = unsigned int;

class Texture {
private:
  auto checkFirstInstantiation_() const noexcept -> void;

  uint id_;
  uint texture_type_;
  uint texture_unit_;

  inline static bool is_first_instance_{true};

public:
  explicit Texture() = default;
  explicit Texture(const char *image_path, uint texture_type, uint slot,
                   uint pixel_type);

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto activate() const noexcept -> void;
  auto deActivate() const noexcept -> void;
  auto deleteTexture() const noexcept -> void;

  auto getTextureUnit() const noexcept -> uint;
};

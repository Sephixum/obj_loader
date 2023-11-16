/**
 * @file Material.hpp
 *
 * @brief A material structure in order to keep
 * in track of different material information.
 *
 */
#pragma once

#include "Texture.hpp"
#include <glm/glm.hpp>
#include <string>

class Material {
private:
  std::string uniform_name_;

  Texture diffuse_texture_;
  Texture specular_texture_;

  float shininess_;

public:
  explicit Material(std::string_view uniform_name, Texture diffuse_texture,
                    Texture specular_texture, float shininess) noexcept;

  auto setUniformName(const std::string_view new_uniform_name) noexcept -> void;
  auto setShininess(float new_shininess) noexcept -> void;
  auto setDiffuseTexture(Texture new_diffuse_texture) noexcept -> void;
  auto setSpecularTexture(Texture new_specular_texture) noexcept -> void;

  [[nodiscard]] auto getUniformName() const noexcept -> std::string;
  [[nodiscard]] auto getShininess() const noexcept -> float;
  [[nodiscard]] auto getDiffuseTexture() const noexcept -> const Texture &;
  [[nodiscard]] auto getSpecularTexture() const noexcept -> const Texture &;
};

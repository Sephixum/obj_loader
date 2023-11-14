/**
 * @file Material.hpp
 *
 * @brief A material structure in order to keep
 * in track of different material information.
 *
 */
#pragma once

#include <glm/glm.hpp>
#include <string>

class Material {
private:
  std::string uniform_name_;
  glm::vec3 diffuse_color_;
  glm::vec3 ambient_color_;
  glm::vec3 specular_color_;
  float shininess_;

public:
  explicit Material(std::string_view uniform_name, glm::vec3 ambient_color,
                    glm::vec3 diffuse_color, glm::vec3 specular_color,
                    float shininess) noexcept;

  auto setUniformName(const std::string_view new_uniform_name) noexcept -> void;
  auto setDiffuseColor(const glm::vec3 new_diffuse_color) noexcept -> void;
  auto setAmbientColor(const glm::vec3 new_ambient_color) noexcept -> void;
  auto setSpecularColor(const glm::vec3 new_specular_color) noexcept -> void;
  auto setShininess(float new_shininess) noexcept -> void;

  [[nodiscard]] auto getUniformName() const noexcept -> std::string;
  [[nodiscard]] auto getDiffuse() const noexcept -> glm::vec3;
  [[nodiscard]] auto getAmbient() const noexcept -> glm::vec3;
  [[nodiscard]] auto getSpecular() const noexcept -> glm::vec3;
  [[nodiscard]] auto getShininess() const noexcept -> float;
};

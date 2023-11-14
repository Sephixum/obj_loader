/**
 * @file Light.hpp
 *
 * @brief A Light structure designed to pass
 * to glsl fragment shader.
 *
 */
#pragma once

#include <glm/glm.hpp>
#include <string>

class Light {
private:
  std::string uniform_name_;
  glm::vec3 diffuse_color_;
  glm::vec3 ambient_color_;
  glm::vec3 specular_color_;
  glm::vec3 position_;

public:
  explicit Light(std::string_view uniform_name, glm::vec3 ambient_color,
                 glm::vec3 diffuse_color, glm::vec3 specular_color,
                 glm::vec3 position) noexcept;

  auto setUniformName(const std::string_view new_uniform_name) noexcept -> void;
  auto setDiffuseColor(const glm::vec3 new_diffuse_color) noexcept -> void;
  auto setAmbientColor(const glm::vec3 new_ambient_color) noexcept -> void;
  auto setSpecularColor(const glm::vec3 new_specular_color) noexcept -> void;
  auto setPosition(const glm::vec3 new_position) noexcept -> void;

  [[nodiscard]] auto getUniformName() const noexcept -> std::string;
  [[nodiscard]] auto getDiffuse() const noexcept -> glm::vec3;
  [[nodiscard]] auto getAmbient() const noexcept -> glm::vec3;
  [[nodiscard]] auto getSpecular() const noexcept -> glm::vec3;
  [[nodiscard]] auto getPosition() const noexcept -> glm::vec3;
};

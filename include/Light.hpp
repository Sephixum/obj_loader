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
  glm::vec3 direction_;
  glm::vec3 position_ = glm::vec3(0.0f, 2.0f, 2.0f);

  float constant_ = 1.0f;
  ;
  float linear_ = 0.09f;
  float quadratic_ = 0.032f;

public:
  explicit Light(std::string_view uniform_name, glm::vec3 ambient_color,
                 glm::vec3 diffuse_color, glm::vec3 specular_color) noexcept;

  auto setUniformName(const std::string_view new_uniform_name) noexcept -> void;
  auto setDiffuseColor(const glm::vec3 new_diffuse_color) noexcept -> void;
  auto setAmbientColor(const glm::vec3 new_ambient_color) noexcept -> void;
  auto setSpecularColor(const glm::vec3 new_specular_color) noexcept -> void;
  auto setDirection(const glm::vec3 new_direction) noexcept -> void;
  auto setPosition(const glm::vec3 new_position) noexcept -> void;
  auto setConstant(float new_constant) noexcept -> void;
  auto setLinear(float new_linear) noexcept -> void;
  auto setQuadratic(float new_quadratic) noexcept -> void;

  [[nodiscard]] auto getUniformName() const noexcept -> std::string;
  [[nodiscard]] auto getDiffuse() const noexcept -> glm::vec3;
  [[nodiscard]] auto getAmbient() const noexcept -> glm::vec3;
  [[nodiscard]] auto getSpecular() const noexcept -> glm::vec3;
  [[nodiscard]] auto getDirection() const noexcept -> glm::vec3;
  [[nodiscard]] auto getPosition() const noexcept -> glm::vec3;
  [[nodiscard]] auto getConstant() const noexcept -> float;
  [[nodiscard]] auto getLinear() const noexcept -> float;
  [[nodiscard]] auto getQuadratic() const noexcept -> float;
};

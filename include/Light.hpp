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
  /*
   * @brief For instance, position is only being used
   * to determine lights direction and point it
   * towards the cube which for this test is at
   * glm::vec3(0.f, 0.f, 0.f).
   * in the book has been said that it is not
   * necessary to have a position though we use
   * it to achieve the same effect as we had in
   * previous commits.
   */
  glm::vec3 position_;

  float constant_;
  float linear_;
  float quadratic_;

public:
  explicit Light(std::string_view uniform_name, glm::vec3 ambient_color,
                 glm::vec3 diffuse_color, glm::vec3 specular_color,
                 glm::vec3 direction,
                 glm::vec3 position = glm::vec3(0.0f, 2.0f, 2.0f),
                 float constant = 1.0f, float linear = 0.09f,
                 float quadratic = 0.032f) noexcept;

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

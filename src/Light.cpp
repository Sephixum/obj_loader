#include "Light.hpp"

// Light::Light(std::string_view uniform_name, glm::vec3 ambient_color,
//              glm::vec3 diffuse_color, glm::vec3 specular_color,
//              glm::vec3 direction, glm::vec3 position) noexcept

Light::Light(std::string_view uniform_name, glm::vec3 ambient_color,
             glm::vec3 diffuse_color, glm::vec3 specular_color,
             glm::vec3 direction, glm::vec3 position, float constant,
             float linear, float quadratic) noexcept
    : uniform_name_(uniform_name), diffuse_color_(diffuse_color),
      ambient_color_(ambient_color), specular_color_(specular_color),
      direction_(direction), position_(position), constant_(constant),
      linear_(linear), quadratic_(quadratic) {}

auto Light::setUniformName(const std::string_view new_uniform_name) noexcept
    -> void {
  uniform_name_ = new_uniform_name;
}

auto Light::setDiffuseColor(const glm::vec3 new_diffuse_color) noexcept
    -> void {
  diffuse_color_ = new_diffuse_color;
}

auto Light::setAmbientColor(const glm::vec3 new_ambient_color) noexcept
    -> void {
  ambient_color_ = new_ambient_color;
}

auto Light::setSpecularColor(const glm::vec3 new_specular_color) noexcept
    -> void {
  specular_color_ = new_specular_color;
}

auto Light::setDirection(const glm::vec3 new_direction) noexcept -> void {
  direction_ = new_direction;
}

auto Light::setPosition(const glm::vec3 new_position) noexcept -> void {
  position_ = new_position;
}

auto Light::setConstant(float new_constant) noexcept -> void {
  constant_ = new_constant;
}

auto Light::setLinear(float new_linear) noexcept -> void {
  linear_ = new_linear;
}

auto Light::setQuadratic(float new_quadratic) noexcept -> void {
  quadratic_ = new_quadratic;
}

auto Light::getUniformName() const noexcept -> std::string {
  return uniform_name_;
}

auto Light::getDiffuse() const noexcept -> glm::vec3 { return diffuse_color_; }

auto Light::getAmbient() const noexcept -> glm::vec3 { return ambient_color_; }

auto Light::getSpecular() const noexcept -> glm::vec3 {
  return specular_color_;
}

auto Light::getDirection() const noexcept -> glm::vec3 { return direction_; }

auto Light::getPosition() const noexcept -> glm::vec3 { return position_; }

auto Light::getConstant() const noexcept -> float { return constant_; }

auto Light::getLinear() const noexcept -> float { return linear_; }

auto Light::getQuadratic() const noexcept -> float { return quadratic_; }

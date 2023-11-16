#include "Material.hpp"

Material::Material(std::string_view uniform_name, glm::vec3 ambient_color,
                   glm::vec3 diffuse_color, glm::vec3 specular_color,
                   float shininess) noexcept
    : uniform_name_(uniform_name), diffuse_color_(diffuse_color),
      ambient_color_(ambient_color), specular_color_(specular_color),
      shininess_(shininess) {}

auto Material::setUniformName(const std::string_view new_uniform_name) noexcept
    -> void {
  uniform_name_ = new_uniform_name;
}

auto Material::setDiffuseColor(const glm::vec3 new_diffuse_color) noexcept
    -> void {
  diffuse_color_ = new_diffuse_color;
}

auto Material::setAmbientColor(const glm::vec3 new_ambient_color) noexcept
    -> void {
  ambient_color_ = new_ambient_color;
}

auto Material::setSpecularColor(const glm::vec3 new_specular_color) noexcept
    -> void {
  specular_color_ = new_specular_color;
}

auto Material::setShininess(float new_shininess) noexcept -> void {
  shininess_ = new_shininess;
}

auto Material::setDiffuseTexture(const Texture &new_diffuse_texture) noexcept
    -> void {
  diffuse_texture_ = new_diffuse_texture;
}

auto Material::setSpecularTexture(const Texture &new_specular_texture) noexcept
    -> void {
  specular_texture_ = new_specular_texture;
}

auto Material::getUniformName() const noexcept -> std::string {
  return uniform_name_;
}

auto Material::getDiffuse() const noexcept -> glm::vec3 {
  return diffuse_color_;
}

auto Material::getAmbient() const noexcept -> glm::vec3 {
  return ambient_color_;
}

auto Material::getSpecular() const noexcept -> glm::vec3 {
  return specular_color_;
}

auto Material::getShininess() const noexcept -> float { return shininess_; }

auto Material::getDiffuseTexture() noexcept -> Texture & {
  return diffuse_texture_;
  ;
}

auto Material::getSpecularTexture() noexcept -> Texture & {
  return specular_texture_;
}

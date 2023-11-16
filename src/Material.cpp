#include "Material.hpp"
#include <algorithm>

Material::Material(std::string_view uniform_name, Texture diffuse_texture,
                   Texture specular_texture, float shininess) noexcept
    : uniform_name_(uniform_name), diffuse_texture_(std::move(diffuse_texture)),
      specular_texture_(std::move(specular_texture)), shininess_(shininess) {}

auto Material::setUniformName(const std::string_view new_uniform_name) noexcept
    -> void {
  uniform_name_ = new_uniform_name;
}

auto Material::setShininess(float new_shininess) noexcept -> void {
  shininess_ = new_shininess;
}

auto Material::setDiffuseTexture(Texture new_diffuse_texture) noexcept -> void {
  diffuse_texture_ = std::move(new_diffuse_texture);
}

auto Material::setSpecularTexture(Texture new_specular_texture) noexcept
    -> void {
  specular_texture_ = std::move(new_specular_texture);
}

auto Material::getUniformName() const noexcept -> std::string {
  return uniform_name_;
}

auto Material::getShininess() const noexcept -> float { return shininess_; }

auto Material::getDiffuseTexture() const noexcept -> const Texture & {
  return diffuse_texture_;
}

auto Material::getSpecularTexture() const noexcept -> const Texture & {
  return specular_texture_;
}

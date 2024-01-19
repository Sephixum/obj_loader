/**
 * @file ShaderProgram.hpp
 *
 * @brief This class represents an id for a
 * shader program.
 *
 */
#pragma once

#include "Light.hpp"
#include "Material.hpp"
#include "globals.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderProgram {
private:
  GLuint id_;
  static auto storeFileToString_(const char *file_name) -> std::string;

public:
  explicit ShaderProgram(const char *vertex_shader_path,
                         const char *fragment_shader_path);

  auto activate() const noexcept -> void;
  static auto deActivate() noexcept -> void;
  auto deleteShader() const noexcept -> void;

  auto setBool(const char *name, bool value) const noexcept -> void;
  auto setInt(const char *name, int32 value) const noexcept -> void;
  auto setFloat(const char *name, f32 value) const noexcept -> void;
  auto setVec2(const char *name, const glm::vec2 &value) const noexcept -> void;
  auto setVec2(const char *name, f32 x, f32 y) const noexcept -> void;
  auto setVec3(const char *name, const glm::vec3 &value) const noexcept -> void;
  auto setVec3(const char *name, f32 x, f32 y, f32 z) const noexcept -> void;
  auto setVec4(const char *name, glm::vec4 &value) const noexcept -> void;
  auto setVec4(const char *name, f32 x, f32 y, f32 z, f32 w) const noexcept
      -> void;
  auto setMat2(const char *name, const glm::mat2 &matrix) const noexcept
      -> void;
  auto setMat3(const char *name, const glm::mat3 &matrix) const noexcept
      -> void;
  auto setMat4(const char *name, const glm::mat4 &matrix) const noexcept
      -> void;
  auto setTextureUnit(const char *name, int32 unit) const noexcept -> void;
  auto setMaterial(const char *name, const Material &material) const noexcept
      -> void;
  auto setLight(const char *name, const Light &light) const noexcept -> void;

  [[nodiscard]] auto getId() const noexcept -> GLuint;
};

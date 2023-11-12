/**
 * @file ShaderProgram.hpp
 *
 * @brief This class represents an id for a
 * shader program.
 *
 */
#pragma once

#include "globals.hpp"

#include <format>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderProgram {
private:
  unsigned int id_;
  static auto storeFileToString_(const char *file_name) -> std::string;

public:
  explicit ShaderProgram(const char *vertex_shader_path,
                         const char *fragment_shader_path);

  auto activate() const noexcept -> void;
  static auto deActivate() noexcept -> void;
  auto deleteShader() const noexcept -> void;

  auto setBool(const char *name, bool value) const noexcept -> void;
  auto setInt(const char *name, int value) const noexcept -> void;
  auto setFloat(const char *name, float value) const noexcept -> void;
  auto setVec2(const char *name, const glm::vec2 &value) const noexcept -> void;
  auto setVec2(const char *name, float x, float y) const noexcept -> void;
  auto setVec3(const char *name, const glm::vec3 &value) const noexcept -> void;
  auto setVec3(const char *name, float x, float y, float z) const noexcept
      -> void;
  auto setVec4(const char *name, glm::vec4 &value) const noexcept -> void;
  auto setVec4(const char *name, float x, float y, float z,
               float w) const noexcept -> void;
  auto setMat2(const char *name, const glm::mat2 &matrix) const noexcept
      -> void;
  auto setMat3(const char *name, const glm::mat3 &matrix) const noexcept
      -> void;
  auto setMat4(const char *name, const glm::mat4 &matrix) const noexcept
      -> void;
  auto setTextureUnit(const char *name, int unit) const noexcept -> void;

  [[nodiscard("Being unused")]] auto getId() const noexcept -> unsigned int;
};

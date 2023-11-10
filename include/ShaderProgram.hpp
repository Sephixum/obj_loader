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
  static auto StoreFileToString(const char *file_name) -> std::string;

public:
  explicit ShaderProgram(const char *vertex_shader_path,
                         const char *fragment_shader_path);

  auto Activate() const noexcept -> void;
  static auto DeActivate() noexcept -> void;
  auto Delete() const noexcept -> void;
  [[nodiscard("Being unused")]] auto GetId() const noexcept -> unsigned int;

  auto SetBool(const char *name, bool value) const noexcept -> void;
  auto SetInt(const char *name, int value) const noexcept -> void;
  auto SetFloat(const char *name, float value) const noexcept -> void;
  auto SetVec2(const char *name, const glm::vec2 &value) const noexcept -> void;
  auto SetVec2(const char *name, float x, float y) const noexcept -> void;
  auto SetVec3(const char *name, const glm::vec3 &value) const noexcept -> void;
  auto SetVec3(const char *name, float x, float y, float z) const noexcept
      -> void;
  auto SetVec4(const char *name, glm::vec4 &value) const noexcept -> void;
  auto SetVec4(const char *name, float x, float y, float z,
               float w) const noexcept -> void;
  auto SetMat2(const char *name, const glm::mat2 &matrix) const noexcept -> void;
  auto SetMat3(const char *name, const glm::mat3 &matrix) const noexcept -> void;
  auto SetMat4(const char *name, const glm::mat4 &matrix) const noexcept -> void;
  auto SetTextureUnit(const char *name, int unit) const noexcept -> void;
};

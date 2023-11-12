#include <ShaderProgram.hpp>
#include <format>

auto ShaderProgram::StoreFileToString(const char *file_name) -> std::string {
  std::ifstream file(file_name, std::ios::binary);
  if (file) {
    return std::string{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};
    if (IS_VERBOSE) {
      std::puts(
          std::format("[SHADER] file \"{}\" loaded successfuly.", file_name)
              .c_str());
    }
  }
  throw std::runtime_error(
      std::format("[SHADER] file \"{}\" did not load correctly.", file_name));
}

ShaderProgram::ShaderProgram(const char *vertex_shader_path,
                             const char *fragment_shader_path) {
  std::string vertex_shader_text{StoreFileToString(vertex_shader_path)};
  std::string fragment_shader_text{StoreFileToString(fragment_shader_path)};

  auto vertex_shader_source{vertex_shader_text.c_str()};
  auto fragment_shader_source{fragment_shader_text.c_str()};

  int success;
  char info_log[512];

  unsigned int vertex_shader{glCreateShader(GL_VERTEX_SHADER)};
  glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
    throw std::runtime_error(std::format("[SHADER] VERTEX failed to compile."
                                         "File : {}.\n"
                                         "Info : {}.\n",
                                         vertex_shader_path, info_log));
  } else if (IS_VERBOSE) {
    std::puts(std::format("[SHADER] VERTEX \"{}\" compiled with success.",
                          vertex_shader_path)
                  .c_str());
  }

  unsigned int fragment_shader{glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
    throw std::runtime_error(
        std::format("[SHADER] FRAGMENT failed to compile.\n"
                    "File : {}.\n"
                    "Info : {}.\n",
                    fragment_shader_path, info_log));
  } else if (IS_VERBOSE) {
    std::puts(std::format("[SHADER] FRAGMENT \"{}\" compiled with success.",
                          fragment_shader_path)
                  .c_str());
  }

  id_ = glCreateProgram();
  glAttachShader(id_, vertex_shader);
  glAttachShader(id_, fragment_shader);
  glLinkProgram(id_);
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id_, 512, nullptr, info_log);
    throw std::runtime_error("[SHADER] PROGRAM failed to link.");
  } else if (IS_VERBOSE) {
    std::puts(std::format("[SHADER] PROGRAM linked with success.").c_str());
  }
}

auto ShaderProgram::Activate() const noexcept -> void { glUseProgram(id_); }

auto ShaderProgram::DeActivate() noexcept -> void { glUseProgram(0); }

auto ShaderProgram::Delete() const noexcept -> void { glDeleteProgram(id_); }

auto ShaderProgram::GetId() const noexcept -> unsigned int { return id_; }

auto ShaderProgram::SetBool(const char *name, bool value) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::SetInt(const char *name, int value) const noexcept -> void {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::SetFloat(const char *name, float value) const noexcept
    -> void {
  glUniform1f(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::SetVec2(const char *name,
                            const glm::vec2 &value) const noexcept -> void {
  glUniform2fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::SetVec2(const char *name, float x, float y) const noexcept
    -> void {
  glUniform2f(glGetUniformLocation(id_, name), x, y);
}

auto ShaderProgram::SetVec3(const char *name,
                            const glm::vec3 &value) const noexcept -> void {
  glUniform3fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::SetVec3(const char *name, float x, float y,
                            float z) const noexcept -> void {
  glUniform3f(glGetUniformLocation(id_, name), x, y, z);
}

auto ShaderProgram::SetVec4(const char *name, glm::vec4 &value) const noexcept
    -> void {
  glUniform4fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::SetVec4(const char *name, float x, float y, float z,
                            float w) const noexcept -> void {
  glUniform4f(glGetUniformLocation(id_, name), x, y, z, w);
}

auto ShaderProgram::SetMat2(const char *name,
                            const glm::mat2 &matrix) const noexcept -> void {
  glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::SetMat3(const char *name,
                            const glm::mat3 &matrix) const noexcept -> void {
  glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::SetMat4(const char *name,
                            const glm::mat4 &matrix) const noexcept -> void {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::SetTextureUnit(const char *name, int unit) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(id_, name), unit);
}

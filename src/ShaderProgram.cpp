#include <ShaderProgram.hpp>
#include <format>

auto ShaderProgram::storeFileToString_(const char *file_name) -> std::string {
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
  std::string vertex_shader_text{storeFileToString_(vertex_shader_path)};
  std::string fragment_shader_text{storeFileToString_(fragment_shader_path)};

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

auto ShaderProgram::activate() const noexcept -> void { glUseProgram(id_); }

auto ShaderProgram::deActivate() noexcept -> void { glUseProgram(0); }

auto ShaderProgram::deleteShader() const noexcept -> void {
  glDeleteProgram(id_);
}

auto ShaderProgram::getId() const noexcept -> unsigned int { return id_; }

auto ShaderProgram::setBool(const char *name, bool value) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::setInt(const char *name, int value) const noexcept -> void {
  glUniform1i(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::setFloat(const char *name, float value) const noexcept
    -> void {
  glUniform1f(glGetUniformLocation(id_, name), value);
}

auto ShaderProgram::setVec2(const char *name,
                            const glm::vec2 &value) const noexcept -> void {
  glUniform2fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::setVec2(const char *name, float x, float y) const noexcept
    -> void {
  glUniform2f(glGetUniformLocation(id_, name), x, y);
}

auto ShaderProgram::setVec3(const char *name,
                            const glm::vec3 &value) const noexcept -> void {
  glUniform3fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::setVec3(const char *name, float x, float y,
                            float z) const noexcept -> void {
  glUniform3f(glGetUniformLocation(id_, name), x, y, z);
}

auto ShaderProgram::setVec4(const char *name, glm::vec4 &value) const noexcept
    -> void {
  glUniform4fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
}

auto ShaderProgram::setVec4(const char *name, float x, float y, float z,
                            float w) const noexcept -> void {
  glUniform4f(glGetUniformLocation(id_, name), x, y, z, w);
}

auto ShaderProgram::setMat2(const char *name,
                            const glm::mat2 &matrix) const noexcept -> void {
  glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::setMat3(const char *name,
                            const glm::mat3 &matrix) const noexcept -> void {
  glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::setMat4(const char *name,
                            const glm::mat4 &matrix) const noexcept -> void {
  glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
                     glm::value_ptr(matrix));
}

auto ShaderProgram::setTextureUnit(const char *name, int unit) const noexcept
    -> void {
  glUniform1i(glGetUniformLocation(id_, name), unit);
}

auto ShaderProgram::setLight(const char *name,
                             const Light &light) const noexcept -> void {
  std::string ambient_component = name;
  ambient_component += ".ambient";

  std::string diffuse_component = name;
  diffuse_component += ".diffuse";

  std::string specular_component = name;
  specular_component += ".specular";

  std::string position = name;
  position += ".position";

  std::string constant = name;
  constant += ".constant";

  std::string linear = name;
  linear += ".linear";

  std::string quadratic = name;
  quadratic += ".quadratic";

  setVec3(ambient_component.c_str(), light.getAmbient());
  setVec3(diffuse_component.c_str(), light.getDiffuse());
  setVec3(specular_component.c_str(), light.getSpecular());
  setVec3(position.c_str(), light.getPosition());
  setFloat(constant.c_str(), light.getConstant());
  setFloat(linear.c_str(), light.getLinear());
  setFloat(quadratic.c_str(), light.getQuadratic());
}

/**
 * @file EBO.hpp
 *
 * @brief A class for Element buffer arrays OpenGL.
 * every intance of this class has it's own unique
 * id.
 *
 */
#pragma once

#include "globals.hpp"

#include <glad/glad.h>
#include <vector>

using Indices = std::vector<GLuint>;

class EBO {
private:
  unsigned int id_;

public:
  EBO();

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
  auto setBufferData(const Indices &incies) const noexcept -> void;
};

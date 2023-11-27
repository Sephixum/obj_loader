/**
 * @file VBO.hpp
 *
 * @brief This class stores and id for an
 * OpenGL vertex buffer object.
 *
 */
#pragma once

#include "Vertex.hpp"
#include <glad/glad.h>

class VBO {
private:
  unsigned int id_;

public:
  VBO();
  VBO(signed long int size, float *vertices) noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
  auto setBufferData(signed long int size, Vertex *vertices) const noexcept
      -> void;
};

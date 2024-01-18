/**
 * @file VBO.hpp
 *
 * @brief This class stores and id for an
 * OpenGL vertex buffer object.
 * note that it is generic and will bind
 * almost any data type.
 *
 */
#pragma once

#include <glad/glad.h>
#include <vector>

class VBO {
private:
  unsigned int id_;

public:
  VBO();

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;

  template <typename Tp>
  auto setBufferData(const std::vector<Tp> &data) const noexcept -> void {
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Tp), data.data(),
                 GL_STATIC_DRAW);
    unBind();
  }
};

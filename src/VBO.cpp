#include "VBO.hpp"

VBO::VBO(signed long int size, float *vertices) noexcept {
  glGenBuffers(1, &id_);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  UnBind();
}

auto VBO::Bind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, id_); }

auto VBO::UnBind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto VBO::Delete() const noexcept -> void { glDeleteBuffers(1, &id_); }

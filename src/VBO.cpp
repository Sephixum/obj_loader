#include "VBO.hpp"

VBO::VBO(signed long int size, float *vertices) noexcept {
  glGenBuffers(1, &id_);
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  unBind();
}

auto VBO::bind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, id_); }

auto VBO::unBind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto VBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &id_); }

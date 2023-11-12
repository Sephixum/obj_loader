#include "EBO.hpp"

EBO::EBO(signed long int size, unsigned int *indices) noexcept {
  glGenBuffers(1, &id_);
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  unBind();
}

auto EBO::bind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

auto EBO::unBind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &id_); }

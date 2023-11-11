#include "EBO.hpp"

EBO::EBO(signed long int size, unsigned int *indices) noexcept {
  glGenBuffers(1, &id_);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  UnBind();
}

auto EBO::Bind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

auto EBO::UnBind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::Delete() const noexcept -> void { glDeleteBuffers(1, &id_); }

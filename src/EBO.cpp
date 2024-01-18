#include "EBO.hpp"

#include <glad/glad.h>

EBO::EBO() { glGenBuffers(1, &id_); }

auto EBO::bind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

auto EBO::unBind() const noexcept -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto EBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &id_); }

auto EBO::setBufferData(const Indices &indices) const noexcept -> void {
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
  unBind();
}

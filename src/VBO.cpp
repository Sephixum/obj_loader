#include "VBO.hpp"

VBO::VBO() { glGenBuffers(1, &id_); }

auto VBO::bind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, id_); }

auto VBO::unBind() const noexcept -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto VBO::deleteBuffer() const noexcept -> void { glDeleteBuffers(1, &id_); }

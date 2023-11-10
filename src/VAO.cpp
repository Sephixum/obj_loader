#include "VAO.hpp"

VAO::VAO() noexcept { glGenVertexArrays(1, &id_); }

auto VAO::Bind() const noexcept -> void { glBindVertexArray(id_); }

auto VAO::UnBind() const noexcept -> void { glBindVertexArray(0); }

auto VAO::LinkVBO(VBO &target_vbo, unsigned int layout,
                  unsigned int number_of_components,
                  unsigned int type_of_components, signed long int stride,
                  void *offset) const noexcept -> void {
  Bind();
  target_vbo.Bind();
  glVertexAttribPointer(layout, number_of_components, type_of_components,
                        GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  target_vbo.UnBind();
  UnBind();
}

auto VAO::Delete() const noexcept -> void { glDeleteVertexArrays(1, &id_); }

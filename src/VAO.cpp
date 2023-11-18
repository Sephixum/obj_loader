#include "VAO.hpp"
#include <cstddef>

VAO::VAO() noexcept { glGenVertexArrays(1, &id_); }

auto VAO::bind() const noexcept -> void { glBindVertexArray(id_); }

auto VAO::unBind() const noexcept -> void { glBindVertexArray(0); }

auto VAO::linkVBO(VBO &target_vbo, unsigned int layout,
                  unsigned int number_of_components,
                  unsigned int type_of_components, signed long int stride,
                  std::size_t offset) const noexcept -> void {
  bind();
  target_vbo.bind();
  glVertexAttribPointer(layout, number_of_components, type_of_components,
                        GL_FALSE, stride, (void *)offset);
  glEnableVertexAttribArray(layout);
  target_vbo.unBind();
  unBind();
}

auto VAO::deleteArray() const noexcept -> void {
  glDeleteVertexArrays(1, &id_);
}

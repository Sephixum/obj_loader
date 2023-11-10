#pragma once

#include "VBO.hpp"
class VAO {
private:
  unsigned int id_;

public:
  explicit VAO() noexcept;
  auto Bind() const noexcept -> void;
  auto UnBind() const noexcept -> void;
  auto LinkVBO(VBO &target_vbo, unsigned int layout,
               unsigned int number_of_components,
               unsigned int type_of_components, signed long int stride,
               void *offset) const noexcept -> void;
  auto Delete() const noexcept -> void;
};

#pragma once

#include <glad/glad.h>

class VBO {
private:
  unsigned int id_;

public:
  explicit VBO(signed long int size, float *vertices) noexcept;
  auto Bind() const noexcept -> void;
  auto UnBind() const noexcept -> void;
  auto Delete() const noexcept -> void;
};

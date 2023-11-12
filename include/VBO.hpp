#pragma once

#include <glad/glad.h>

class VBO {
private:
  unsigned int id_;

public:
  explicit VBO(signed long int size, float *vertices) noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
};

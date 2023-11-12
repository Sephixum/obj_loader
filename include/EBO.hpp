#pragma once

#include <glad/glad.h>

class EBO {
private:
  unsigned int id_;

public:
  explicit EBO(signed long int size, unsigned int *indices) noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
};

#pragma once

#include <glad/glad.h>

class EBO {
private:
  unsigned int id_;

public:
  explicit EBO(signed long int size, unsigned int *indices) noexcept;

  auto Bind() const noexcept -> void;
  auto UnBind() const noexcept -> void;
  auto Delete() const noexcept -> void;
};

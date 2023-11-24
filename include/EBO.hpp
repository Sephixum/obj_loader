/**
 * @file EBO.hpp
 *
 * @brief A class for Eemeent buffer arrays OpenGL.
 * every intance of this class has it's own unique
 * id.
 *
 */
#pragma once

#include <glad/glad.h>

class EBO {
private:
  unsigned int id_;

public:
  EBO();
  EBO(signed long int size, unsigned int *indices) noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto deleteBuffer() const noexcept -> void;
  auto setBufferData(signed long int size, unsigned int *indices) const noexcept
      -> void;
};

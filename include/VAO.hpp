/**
 * @file VAO.hpp
 *
 * @brief This class is an OpenGL vertex-
 * array object that stores an id for one
 * of these objects.
 *
 */
#pragma once

#include "VBO.hpp"

#include <cstddef>

class VAO {
private:
  unsigned int id_;

public:
  explicit VAO() noexcept;

  auto bind() const noexcept -> void;
  auto unBind() const noexcept -> void;
  auto linkVBO(VBO &target_vbo, unsigned int layout,
               unsigned int number_of_components,
               unsigned int type_of_components, signed long int stride,
               std::size_t offset) const noexcept -> void;
  auto deleteArray() const noexcept -> void;
};

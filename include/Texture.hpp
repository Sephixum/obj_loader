/**
 * @file Texture.hpp
 *
 * @brief This class controlls binding, unbinding and
 * id for a texture object.
 *
 */
#pragma once

#include <glad/glad.h>
#include <string>

struct Texture {
  GLuint id;
  std::string type;
  std::string path;
};

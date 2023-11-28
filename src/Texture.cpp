#include "Texture.hpp"
#include <filesystem>
#include <stb_image.h>
#include <stdexcept>

Texture::Texture(std::string image_path, std::string type_name)
    : type_(type_name) {
  int image_width, image_height, channel_numbers;
  auto data = stbi_load(image_path.c_str(), &image_width, &image_height,
                        &channel_numbers, 0);

  if (!data) {
    throw std::runtime_error(
        std::format("[TEXTURE] cannot load {}.\n REASON : ", image_path.c_str(),
                    stbi_failure_reason()));
  }

  std::filesystem::path temp_path = image_path;
  file_name_ = temp_path.filename().string();

  GLenum format;
  switch (channel_numbers) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  }

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}

auto Texture::bind() const noexcept -> void {
  glBindTexture(GL_TEXTURE_2D, id_);
}

auto Texture::unBind() noexcept -> void { glBindTexture(GL_TEXTURE_2D, 0); }

auto Texture::activate(GLenum slot) const noexcept -> void {
  glActiveTexture(slot);
}

auto Texture::setType(std::string_view new_type) noexcept -> void {
  type_ = new_type;
}

auto Texture::setFileName(std::string_view new_file_name) noexcept -> void {
  file_name_ = new_file_name;
}

auto Texture::getType() const noexcept -> std::string { return type_; }

auto Texture::getFileName() const noexcept -> std::string { return file_name_; }

auto Texture::getId() const noexcept -> GLuint { return id_; }

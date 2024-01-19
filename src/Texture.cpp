#include "Texture.hpp"
#include "globals.hpp"

#include <filesystem>
#include <format>
#include <memory>
#include <stb_image.h>
#include <stdexcept>

auto Texture::pushToGraphicsCard_(unsigned char *data) noexcept -> void {
  GLenum format;
  switch (image_info_.channels) {
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
  glBindTexture(kTexture_type, id_);
  glTexImage2D(kTexture_type, 0, kInternal_format, image_info_.width,
               image_info_.heigt, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(kTexture_type);

  // Set texture parameters
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(kTexture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(kTexture_type, 0);
}

Texture::Texture() {
  glGenTextures(1, &id_);

  glBindTexture(kTexture_type, id_);

  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(kTexture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(kTexture_type, 0);

  MSG_LOG(std::format("default constructed with id {}", id_).c_str());
}

Texture::Texture(std::string image_path, std::string type_name)
    : type_(type_name) {
  int image_width, image_height, channel_numbers;
  auto image_data = stbi_load(image_path.c_str(), &image_width, &image_height,
                              &channel_numbers, 0);

  if (!image_data) {
    MSG_LOG(std::format("cannot load {}.\n REASON : ", image_path.c_str(),
                        stbi_failure_reason()));
    throw std::runtime_error("Error! check logs.");
  }

  image_info_.width = image_width;
  image_info_.heigt = image_height;
  image_info_.channels = channel_numbers;

  std::filesystem::path temp_path = image_path;
  file_name_ = temp_path.filename().string();

  pushToGraphicsCard_(image_data);

  stbi_image_free(image_data);

  MSG_LOG(
      std::format("\"{}\" loaded with success with id {}.", image_path, id_));
}

Texture::~Texture() {}

auto Texture::bind(GLenum slot) const noexcept -> void {
  glActiveTexture(slot);
  glBindTexture(kTexture_type, id_);
}

auto Texture::bind() const noexcept -> void {
  glBindTexture(kTexture_type, id_);
}

auto Texture::unBind() noexcept -> void { glBindTexture(GL_TEXTURE_2D, 0); }

auto Texture::activate(GLenum slot) const noexcept -> void {
  glActiveTexture(slot);
}

auto Texture::deleteTexture() const noexcept -> void {
  glDeleteTextures(1, &id_);
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

auto Texture::getImageInfo() const noexcept -> ImageData { return image_info_; }

auto Texture::deepCopy(Texture &target, Texture &destination) noexcept -> void {
  auto target_image_info = target.getImageInfo();

  GLenum format;
  switch (target_image_info.channels) {
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

  std::unique_ptr<unsigned char[]> new_image_data(
      new unsigned char[target_image_info.width * target_image_info.heigt *
                        kInternal_channel_nr]);

  target.bind();
  glGetTexImage(kTexture_type, 0, kInternal_format, GL_UNSIGNED_BYTE,
                new_image_data.get());
  target.unBind();

  destination.deleteTexture();
  glGenTextures(1, &destination.id_);
  destination.bind();
  glTexImage2D(kTexture_type, 0, kInternal_format, target_image_info.width,
               target_image_info.heigt, 0, format, GL_UNSIGNED_BYTE,
               new_image_data.get());
  glGenerateMipmap(kTexture_type);
  destination.unBind();

  MSG_LOG(
      std::format("[TEXTURE] deep copied texture with id {}", destination.id_)
          .c_str());
}

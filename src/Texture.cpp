#include "Texture.hpp"
#include <filesystem>
#include <stb_image.h>
#include <stdexcept>

auto Texture::pushToGraphicsCard_(unsigned char *data) noexcept -> void {
  GLenum format;
  switch (image_info.channels) {
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
  glTexImage2D(kTexture_type, 0, kInternal_format, image_info.width,
               image_info.heigt, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(kTexture_type);

  // Set texture parameters
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(kTexture_type, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(kTexture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(std::string image_path, std::string type_name)
    : type_(type_name) {
  int image_width, image_height, channel_numbers;
  auto image_data = stbi_load(image_path.c_str(), &image_width, &image_height,
                              &channel_numbers, 0);

  if (!image_data) {
    throw std::runtime_error(
        std::format("[TEXTURE] cannot load {}.\n REASON : ", image_path.c_str(),
                    stbi_failure_reason()));
  }

  image_info.width = image_width;
  image_info.heigt = image_height;
  image_info.channels = channel_numbers;

  std::filesystem::path temp_path = image_path;
  file_name_ = temp_path.filename().string();

  pushToGraphicsCard_(image_data);

  stbi_image_free(image_data);

  std::puts(std::format("[TEXTURE] \"{}\" loaded with success with id {}.",
                        image_path, id_)
                .c_str());
}

Texture::Texture(const Texture &other) noexcept {
  id_ = other.getId();
  type_ = other.getType();
  file_name_ = other.getFileName();
  image_info = other.getImageInfo();

  std::unique_ptr<unsigned char[]> new_image_data(
      new unsigned char[image_info.width * image_info.heigt * 4]);

  other.bind();
  glGetTexImage(kTexture_type, 0, kInternal_format, GL_UNSIGNED_BYTE,
                new_image_data.get());
  other.unBind();

  pushToGraphicsCard_(new_image_data.get());

  std::puts(
      std::format("[TEXTURE] copied with success with id {}.", id_).c_str());
}

auto Texture::operator=(const Texture &other) noexcept -> Texture & {
  if (&other == this) {
    return *this;
  }

  std::unique_ptr<unsigned char[]> new_image_data(
      new unsigned char[image_info.width * image_info.heigt * 4]);

  other.bind();
  glGetTexImage(kTexture_type, 0, kInternal_format, GL_UNSIGNED_BYTE,
                new_image_data.get());
  other.unBind();

  pushToGraphicsCard_(new_image_data.get());

  std::puts(
      std::format("[TEXTURE] copied with success with id {}.", id_).c_str());

  return *this;
}

Texture::~Texture() {}

auto Texture::bind() const noexcept -> void {
  glBindTexture(kTexture_type, id_);
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

auto Texture::getImageInfo() const noexcept -> ImageData { return image_info; }

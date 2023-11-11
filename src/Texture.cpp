#include "Texture.hpp"

Texture::Texture(const char *image_path, uint texture_type, uint slot,
                 uint pixel_type)
    : texture_type_(texture_type), texture_unit_(slot) {

  CheckFirstInstantiation();

  int image_width, image_height, number_of_color_channels;
  auto image_bytes = stbi_load(image_path, &image_width, &image_height,
                               &number_of_color_channels, 0);
  if (image_bytes) {
    glGenTextures(1, &id_);
    glActiveTexture(texture_unit_);
    glBindTexture(texture_type_, id_);

    glTexParameteri(texture_type_, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(texture_type_, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);

    uint format;
    switch (number_of_color_channels) {
    case 3: {
      format = GL_RGB;
    } break;
    case 4: {
      format = GL_RGBA;
    } break;
    default: {
      throw std::runtime_error(std::format(
          "[TEXTURE] format cannot be supported for \"{}\".", image_path));
    } break;
    }

    glTexImage2D(texture_type_, 0, format, image_width, image_height, 0, format,
                 pixel_type, image_bytes);
    glGenerateMipmap(texture_type_);

    stbi_image_free(image_bytes);
    glBindTexture(texture_type_, 0);
  } else {
    throw std::runtime_error(
        std::format("[TEXTURE] {} could not be loaded.", image_path));
  }
}

auto Texture::Bind() const noexcept -> void {
  glBindTexture(texture_type_, id_);
}

auto Texture::UnBind() const noexcept -> void {
  glBindTexture(texture_type_, 0);
}

auto Texture::Activate() const noexcept -> void {
  glActiveTexture(texture_unit_);
}

auto Texture::DeActivate() const noexcept -> void { glDisable(texture_type_); }

auto Texture::Delete() const noexcept -> void { glDeleteTextures(1, &id_); }

auto Texture::GetTextureUnit() const noexcept -> uint { return texture_unit_; }

auto Texture::CheckFirstInstantiation() const noexcept -> void {
  if (is_first_instance_) {
    stbi_set_flip_vertically_on_load(true);
    is_first_instance_ = false;
  }
}

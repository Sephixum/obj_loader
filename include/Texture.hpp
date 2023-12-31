/**
 * @file Texture.hpp
 *
 * @brief This class controlls binding, unbinding and
 * id for a texture object.
 *
 */
#pragma once

#include <format>
#include <glad/glad.h>
#include <string>

class Texture {
private:
  struct ImageData {
    int width;
    int heigt;
    int channels;
  };

  auto pushToGraphicsCard_(unsigned char *data) noexcept -> void;

  GLuint id_;
  std::string type_;
  std::string file_name_;
  ImageData image_info_;

  constexpr static GLenum kTexture_type = GL_TEXTURE_2D;
  constexpr static GLenum kInternal_format = GL_RGBA;
  constexpr static int kInternal_channel_nr = 4;

public:
  Texture();
  Texture(std::string image_path, std::string type_name);
  Texture(Texture &&other) noexcept = default;
  auto operator=(Texture &&rhs) noexcept -> Texture & = default;
  Texture(const Texture &other) noexcept = default;
  auto operator=(const Texture &rhs) noexcept -> Texture & = default;
  ~Texture();

  auto bind(GLenum slot) const noexcept -> void;
  auto bind() const noexcept -> void;
  static auto unBind() noexcept -> void;
  auto activate(GLenum slot) const noexcept -> void;
  auto deleteTexture() const noexcept -> void;

  auto setType(std::string_view new_type) noexcept -> void;
  auto setFileName(std::string_view new_file_name) noexcept -> void;

  auto getType() const noexcept -> std::string;
  auto getFileName() const noexcept -> std::string;
  auto getId() const noexcept -> GLuint;
  auto getImageInfo() const noexcept -> ImageData;

  static auto deepCopyTexture(Texture &target, Texture &destination) noexcept
      -> void;
};

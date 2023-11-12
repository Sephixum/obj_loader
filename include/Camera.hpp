#pragma once

#include "ShaderProgram.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera {
private:
  auto keyboardInputProccess_(float delta_time) -> void;
  auto mouseInputProccess_(float delta_time) -> void;

  GLFWwindow *target_window_;
  float fov_;
  float aspect_ratio_;
  float near_plane_;
  float far_plane_;

  bool first_move_ = true;
  float sensitivity_ = 0.1f;
  float speed_ = 5.f;
  float last_x_ = 0.0f;
  float last_y_ = 0.0f;
  float pitch_ = 0.0f;
  float yaw_ = -90.f;

  glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
  /*
   * We will not need camera_right due to
   * use of glm::lookAt.
   */
  // glm::vec3 camera_right;

  glm::vec3 camera_position_ = glm::vec3(0.f, 0.f, 0.f);
  glm::vec3 camera_orientation_ = glm::vec3(0.0f, 0.0f, -1.0f);
  /*
   * projection * lookat
   */
  glm::mat4 camera_matrix_ = glm::mat4(1.0f);

public:
  explicit Camera(float aspect_ratio, glm::vec3 position,
                  GLFWwindow *target_window, float fov = 66.f,
                  float near_plane = 0.1f, float far_plane = 100.f) noexcept;

  auto updateCameraMatrix() noexcept -> void;
  auto update(float delta_time) noexcept -> void;

  auto setFov(float fov) noexcept -> void;
  auto setNearPlane(float new_near_plane) noexcept -> void;
  auto setFarPlane(float new_far_plane) noexcept -> void;
  auto setAspectRatio(float new_aspect_ratio) noexcept -> void;
  auto setCameraMatrixToShader(ShaderProgram &shader,
                               const char *uniform_name) const noexcept -> void;
  auto setCameraPosition(glm::vec3 new_position) noexcept -> void;

  [[nodiscard]] auto getCameraMatrix() const noexcept -> glm::mat4;
  [[nodiscard]] auto getCameraPosition() const noexcept -> glm::vec3;
  [[nodiscard]] auto getFov() const noexcept -> float;
  [[nodiscard]] auto getNearPlane() const noexcept -> float;
  [[nodiscard]] auto getFarPlane() const noexcept -> float;
};

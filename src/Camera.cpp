#include "Camera.hpp"

Camera::Camera(float aspect_ratio, glm::vec3 camera_position) noexcept
    : aspect_ratio_(aspect_ratio), first_move_(true), sensitivity_(0.1f),
      speed_(0.1f), last_x_(0.0f), last_y_(0.0f), pitch_(0.0f),
      yaw_(-90.f), camera_up_(glm::vec3(0.0f, 1.0f, 0.0f)),
      camera_position_(camera_position),
      camera_orientation_(glm::vec3(0.0f, 0.0f, -1.0f)),
      camera_matrix_(glm::mat4(1.0f)) {}

auto Camera::UpdateCameraMatrix(float fov, float near_plane,
                                float far_plane) noexcept -> void {
  auto projection = glm::perspective(
      glm::radians(fov), aspect_ratio_, near_plane, far_plane);
  auto view = glm::lookAt(camera_position_,
                          camera_position_ + camera_orientation_, camera_up_);

  camera_matrix_ = projection * view;
}

auto Camera::SetCameraMatrixToShader(ShaderProgram &shader_program,
                                     const char *uniform_name) const noexcept
    -> void {
  shader_program.SetMat4(uniform_name, camera_matrix_);
}

auto Camera::GetCameraMatrix() const noexcept -> glm::mat4 {
  return camera_matrix_;
}

auto Camera::GetCameraPosition() const noexcept -> glm::vec3 {
  return camera_position_;
}

#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/quaternion_geometric.hpp>

Camera::Camera(float aspect_ratio, glm::vec3 camera_position,
               GLFWwindow *target_window, float fov, float near_plane,
               float far_plane) noexcept
    : target_window_(target_window), fov_(fov), aspect_ratio_(aspect_ratio),
      near_plane_(near_plane), far_plane_(far_plane),
      camera_position_(camera_position) {}

auto Camera::updateCameraMatrix() noexcept -> void {
  auto projection =
      glm::perspective(glm::radians(fov_), aspect_ratio_, near_plane_, far_plane_);
  auto view = glm::lookAt(camera_position_,
                          camera_position_ + camera_orientation_, camera_up_);

  camera_matrix_ = projection * view;
}

auto Camera::setCameraMatrixToShader(ShaderProgram &shader_program,
                                     const char *uniform_name) const noexcept
    -> void {
  shader_program.setMat4(uniform_name, camera_matrix_);
}

auto Camera::getCameraMatrix() const noexcept -> glm::mat4 {
  return camera_matrix_;
}

auto Camera::getCameraPosition() const noexcept -> glm::vec3 {
  return camera_position_;
}

auto Camera::keyboardInputProccess_(float delta_time) -> void {
  auto temp_speed = speed_ * delta_time;
  if (glfwGetKey(target_window_, GLFW_KEY_W) == GLFW_PRESS) {
    camera_position_ += temp_speed * camera_orientation_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_S) == GLFW_PRESS) {
    camera_position_ -= temp_speed * camera_orientation_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_A) == GLFW_PRESS) {
    camera_position_ +=
        temp_speed *
        glm::normalize(glm::cross(camera_up_, camera_orientation_));
  }
  if (glfwGetKey(target_window_, GLFW_KEY_D) == GLFW_PRESS) {
    camera_position_ -=
        temp_speed *
        glm::normalize(glm::cross(camera_up_, camera_orientation_));
  }
  if (glfwGetKey(target_window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
    camera_position_ += temp_speed * camera_up_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    camera_position_ -= temp_speed * camera_up_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed_ = 15.0f;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed_ = 5.0f;
  }
}

auto Camera::update(float delta_time) noexcept -> void {
  keyboardInputProccess_(delta_time);
  // MouseInputProccess(delta_time);
}

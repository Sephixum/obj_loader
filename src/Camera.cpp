#include "Camera.hpp"
#include <algorithm>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/gtc/quaternion.hpp>

float Camera::current_time_ = 0.f;
float Camera::delta_time_ = 0.f;
float Camera::last_time_ = 0.f;

auto Camera::keyboardInputProccess_() noexcept -> void {
  auto temp_speed = speed_ * delta_time_;
  if (glfwGetKey(target_window_, GLFW_KEY_W) == GLFW_PRESS) {
    position_ += temp_speed * orientation_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_S) == GLFW_PRESS) {
    position_ -= temp_speed * orientation_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_A) == GLFW_PRESS) {
    position_ += temp_speed * glm::normalize(glm::cross(up_, orientation_));
  }
  if (glfwGetKey(target_window_, GLFW_KEY_D) == GLFW_PRESS) {
    position_ -= temp_speed * glm::normalize(glm::cross(up_, orientation_));
  }
  if (glfwGetKey(target_window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
    position_ += temp_speed * up_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    position_ -= temp_speed * up_;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed_ = 15.0f;
  }
  if (glfwGetKey(target_window_, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    speed_ = 5.0f;
  }
}

auto Camera::mouseInputProccess_() noexcept -> void {
  if (glfwGetMouseButton(target_window_, GLFW_MOUSE_BUTTON_LEFT) ==
      GLFW_PRESS) {
    glfwSetInputMode(target_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double mouse_pos_x;
    double mouse_pos_y;
    glfwGetCursorPos(target_window_, &mouse_pos_x, &mouse_pos_y);

    if (first_move_) {
      last_x_ = static_cast<float>(mouse_pos_x);
      last_y_ = static_cast<float>(mouse_pos_y);
      first_move_ = false;
    }

    float x_offset = mouse_pos_x - last_x_;
    float y_offset = last_y_ - mouse_pos_y;

    last_x_ = mouse_pos_x;
    last_y_ = mouse_pos_y;

    x_offset *= sensitivity_;
    y_offset *= sensitivity_;

    yaw_ += x_offset;
    pitch_ += y_offset;

    pitch_ = std::clamp(pitch_, -89.9f, 89.9f);

    glm::vec3 new_orientation;
    new_orientation.x =
        std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
    new_orientation.y = std::sin(glm::radians(pitch_));
    new_orientation.z =
        std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));

    orientation_ = new_orientation;

  } else if (glfwGetMouseButton(target_window_, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(target_window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    first_move_ = true;
  }
}

auto Camera::updateMatrix_() noexcept -> glm::mat4 {
  auto projection = glm::perspective(glm::radians(fov_), aspect_ratio_,
                                     near_plane_, far_plane_);
  auto view = glm::lookAt(position_, position_ + orientation_, up_);
  matrix_ = projection * view;

  return matrix_;
}

Camera::Camera(float aspect_ratio, glm::vec3 position,
               GLFWwindow *target_window, float fov, float near_plane,
               float far_plane) noexcept
    : target_window_(target_window), fov_(fov), aspect_ratio_(aspect_ratio),
      near_plane_(near_plane), far_plane_(far_plane), position_(position) {}

auto Camera::update() noexcept -> void {
  current_time_ = glfwGetTime();
  delta_time_ = current_time_ - last_time_;
  last_time_ = current_time_;

  keyboardInputProccess_();
  mouseInputProccess_();
  updateMatrix_();
}

auto Camera::setFov(float fov) noexcept -> void { fov_ = fov; }

auto Camera::setNearPlane(float new_near_plane) noexcept -> void {
  near_plane_ = new_near_plane;
}

auto Camera::setFarPlane(float new_far_plane) noexcept -> void {
  far_plane_ = new_far_plane;
}

auto Camera::setAspectRatio(float new_aspect_ratio) noexcept -> void {
  aspect_ratio_ = new_aspect_ratio;
}

auto Camera::setPosition(glm::vec3 new_position) noexcept -> void {
  position_ = new_position;
}

auto Camera::getCameraMatrix() const noexcept -> glm::mat4 { return matrix_; }

auto Camera::getCameraPosition() const noexcept -> glm::vec3 {
  return position_;
}

auto Camera::getFov() const noexcept -> float { return fov_; }

auto Camera::getNearPlane() const noexcept -> float { return near_plane_; }

auto Camera::getFarPlane() const noexcept -> float { return far_plane_; }

#pragma once

#include "ShaderProgram.hpp"
#include <glm/ext.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera {
private:
  float aspect_ratio_;
  bool first_move_;
  float sensitivity_;
  float speed_;
  float last_x_;
  float last_y_;
  float pitch_;
  float yaw_;

  glm::vec3 camera_up_;
  /*
   * We will not need camera_right due to
   * use of glm::lookAt.
   */
  // glm::vec3 camera_right;

  glm::vec3 camera_position_;
  glm::vec3 camera_orientation_;
  /*
   * projection * lookat
   */
  glm::mat4 camera_matrix_;

public:
  explicit Camera(float aspect_ratio, glm::vec3 position) noexcept;

  auto UpdateCameraMatrix(float fov, float near_plane, float far_plane) noexcept
      -> void;
  auto SetCameraMatrixToShader(ShaderProgram &shader,
                               const char *uniform_name) const noexcept -> void;
  auto GetCameraMatrix() const noexcept -> glm::mat4;
  auto GetCameraPosition() const noexcept -> glm::vec3;
  auto Update() noexcept -> void;
};

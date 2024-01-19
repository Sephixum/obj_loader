cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)

project(
  LearnOpenGL_part1
  VERSION 0.1.0
  LANGUAGES C CXX
  DESCRIPTION "A review on what I have learned from part 1")

add_subdirectory(deps/)

add_executable(output)
target_sources(
  output
  PRIVATE src/main.cpp
          src/ShaderProgram.cpp
          src/VBO.cpp
          src/VAO.cpp
          src/EBO.cpp
          src/Utils.cpp
          src/stb_image_activator.cpp
          src/Texture.cpp
          src/Camera.cpp
          src/Material.cpp
          src/Light.cpp
          src/Mesh.cpp
          src/Model.cpp)
target_link_libraries(output PRIVATE glfw glad assimp)
target_include_directories(output PRIVATE include/ deps/stb_image/)

add_custom_command(
  TARGET POST_BUILD
  output
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${ASSETS_DIR}
          $<TARGET_FILE_DIR:output>/assets
  COMMENT "Copying shaders and textures to binary directory")

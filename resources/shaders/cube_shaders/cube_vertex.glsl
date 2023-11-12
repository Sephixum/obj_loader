#version 330 core

//==============VAO input===============
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex_coords;
layout (location = 2) in vec3 aNormal;
//======================================

//=======output of vertex sahder========
out vec2 tex_coords;
out vec3 normal_vector;
//======================================

//==============uniforms================
uniform mat4 model_matrix;
uniform mat4 camera_matrix;
//======================================


//===============main code==============
void main() {
   gl_Position = camera_matrix * model_matrix * vec4(aPos, 1.0f);
   tex_coords = aTex_coords;
   normal_vector = aNormal;
}

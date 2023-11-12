#version 330 core

//==============VAO input===============
layout (location = 0) in vec3 aPos;
//======================================

//=======output of vertex sahder========
//======================================

//==============uniforms================
uniform mat4 model_matrix;
uniform mat4 camera_matrix;
//======================================


//===============main code==============
void main() {
   gl_Position = camera_matrix * model_matrix * vec4(aPos, 1.0f);
}

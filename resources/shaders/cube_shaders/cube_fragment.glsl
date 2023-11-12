#version 330 core

//=======output of fragment sahder========
out vec4 FragColor;
//========================================

//========input to fragment shader========
in vec2 tex_coords;
in vec3 normal_vector;
//========================================

//===============uniforms=================
uniform sampler2D tex0;
//========================================

//===============main code================
void main() {
   FragColor = texture(tex0, tex_coords);
}

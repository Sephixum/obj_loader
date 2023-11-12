#version 330 core

//=======output of fragment sahder========
out vec4 FragColor;
//========================================

//========input to fragment shader========
in vec2 tex_coords;
//========================================

//===============uniforms=================
uniform sampler2D tex0;
//========================================

//===============main code================
void main() {
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   FragColor = texture(tex0, tex_coords);
}

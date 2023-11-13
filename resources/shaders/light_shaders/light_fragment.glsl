#version 330 core

//=======output of fragment sahder========
out vec4 FragColor;
//========================================

//========input to fragment shader========
//========================================

//===============uniforms=================
uniform vec3 light_color;
//========================================

//===============main code================
void main() {
   vec3 result = light_color;
   FragColor = vec4(light_color ,1.0f);
}

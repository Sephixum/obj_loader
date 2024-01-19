#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoords;

out vec3 vtof_Color;
out vec2 vtof_TexCoords;

uniform mat4 model;
uniform mat4 camera;

void main()
{
    vtof_TexCoords = aTexCoords;    
    vtof_Color = aColor;
    gl_Position = camera * model * vec4(aPos, 1.0);
}

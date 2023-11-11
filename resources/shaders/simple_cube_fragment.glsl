#version 330 core

out vec4 FragColor;

in vec2 tex_coords;

uniform sampler2D tex0;

void main() {
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   FragColor = texture(tex0, tex_coords);
}

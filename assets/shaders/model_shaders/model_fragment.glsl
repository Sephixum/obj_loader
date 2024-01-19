#version 330 core
out vec4 FragColor;

in vec3 vtof_Color;
in vec2 vtof_TexCoords;

uniform sampler2D diffuse1;
uniform sampler2D specular1;

void main()
{    
    // FragColor = texture(diffuse1, vtof_TexCoords);
    // FragColor = texture(specular1, vtof_TexCoords);
    // FragColor = vec4(vtof_Color, 1.0f);
    FragColor = mix(
      texture(diffuse1, vtof_TexCoords),
      texture(specular1, vtof_TexCoords), 
      0.3f);
}

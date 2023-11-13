#version 330 core

/**
* Output of fragment sahder
*
*/
out vec4 FragColor;

/**
* Input to fragment shader
*
*/
in vec2 tex_coords;
in vec3 normal_vector;
in vec3 fragment_position;

/**
* Uniforms
*
*/
uniform sampler2D tex0;
uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 object_color;
uniform vec3 camera_position;

void main() {
   /**
   * Preparations for different lighting
   * components.
   *
   */
   vec3 normalized_normal = normalize(normal_vector);
   vec3 light_direction = normalize(light_position - fragment_position);
   vec3 camera_direction = normalize(camera_position - fragment_position);

   /**
   * Ambient lighting.
   *
   */
   float ambient_strength = 0.08;
   vec3 ambient_color = light_color * ambient_strength;


   /**
   * Diffuse lighting.
   *
   */
   float diffuse_strength = max(dot(normalized_normal, light_direction), 0.0f);
   vec3 diffuse_color = light_color * diffuse_strength;

   /**
   * Specular lighting.
   *
   */
   float specular_strength = 0.5;
   vec3 reflect_direction = reflect(-light_direction, normalized_normal);
   float specular_intensity =
	pow(
	max(dot(camera_direction, reflect_direction), 0.0f), 128
	);
   vec3 specular_lighting = 
   	light_color * specular_strength * specular_intensity;

   vec3 result = object_color * 
   	(ambient_color + diffuse_color + specular_lighting);
   FragColor = vec4(result, 1.0f);
   // FragColor = vec4(result, 1.0f) * texture(tex0, tex_coords);
}

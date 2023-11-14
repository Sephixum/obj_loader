#version 330 core

/**
* Strucs
*
*/
struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   vec3 position;
};

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
uniform Material material;
uniform Light light;

void main() {

   /**
   * Ambient lighting.
   *
   */
   vec3 ambient_lighting = light.ambient * material.ambient;


   /**
   * Diffuse lighting.
   *
   */
   vec3 normalized_normal = normalize(normal_vector);
   vec3 light_direction = normalize(light.position - fragment_position);
   float diffuse_strength = max(dot(normalized_normal, light_direction), 0.0f);
   vec3 diffuse_lighting = light.diffuse * (diffuse_strength * material.diffuse);

   /**
   * Specular lighting.
   *
   */
   vec3 camera_direction = normalize(camera_position - fragment_position);
   vec3 reflect_direction = reflect(-light_direction, normalized_normal);
   float specular_intensity =
	pow(
	max(dot(camera_direction, reflect_direction), 0.0f), material.shininess
	);
   vec3 specular_lighting = 
   	light.specular * (specular_intensity * material.specular);

   vec3 result = 
   	(ambient_lighting + diffuse_lighting + specular_lighting);
   FragColor = vec4(result, 1.0f);
}

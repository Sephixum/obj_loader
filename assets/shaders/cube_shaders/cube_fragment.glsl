#version 330 core

/**
* Strucs
*
*/ struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light {
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
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
uniform vec3 camera_position;
uniform Material material;
uniform Light light;

void main() {

   /**
   * Ambient lighting.
   *
   */
   vec3 ambient_lighting = light.ambient * vec3(texture(material.diffuse, tex_coords));


   /**
   * Diffuse lighting.
   *
   */
   vec3 normalized_normal = normalize(normal_vector);
   vec3 light_direction = normalize(light.position - fragment_position);
   float diffuse_strength = max(dot(normalized_normal, light_direction), 0.0f);
   vec3 diffuse_lighting = light.diffuse * 
   			   diffuse_strength * 
			   texture(material.diffuse, tex_coords).rgb;

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
   	light.specular *
	specular_intensity *
	texture(material.specular, tex_coords).rgb;
	
   /**
   * Attenuation.
   *
   */
   float distance = length(light.position - fragment_position);
   // float attenuation = 
   // 	1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   float attenuation = 
   	1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   
   ambient_lighting *= attenuation;
   diffuse_lighting *= attenuation;
   specular_lighting *= attenuation;
   vec3 result = 
   	(ambient_lighting + diffuse_lighting + specular_lighting);
   FragColor = vec4(result, 1.0f);
   // vec4 test = texture(material.specular, tex_coords);
   // FragColor = vec4(test);
}

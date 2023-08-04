#version 330
out vec4 FragColor;

// Structs
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float shininess;
};

struct Light {
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 frag_pos;

uniform vec3 view_pos;

void main()
{
	// Ambient 
	
	vec3 ambient = light.ambient * material.ambient;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 light_direction = normalize(light.position - frag_pos);

	float diff = max(dot(light_direction, norm), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	// Specular
	vec3 view_direction = normalize(view_pos - frag_pos);
	vec3 reflect_direction = reflect(-light_direction, norm);

	float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);


	vec3 result_color = ambient + diffuse + specular;

	FragColor =  vec4(result_color, 1.0);
}


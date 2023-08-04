#version 330
out vec4 FragColor;


in vec3 normal;
in vec3 frag_pos;

uniform vec3 model_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main()
{
	

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 light_direction = normalize(light_pos - frag_pos);

	float diff = max(dot(light_direction, norm), 0.0);
	vec3 diffuse = diff * light_color;
	
	// Ambient 
	float ambient_strength = 0.1;
	vec3 ambient = ambient_strength * light_color;

	// Specular
	float specular_strength = 0.5;
	
	vec3 view_direction = normalize(view_pos - frag_pos);
	vec3 reflect_direction = reflect(-light_direction, norm);

	float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), 64);
	vec3 specular = specular_strength * spec * light_color;


	vec3 result_color = (ambient + diffuse + specular) * model_color;

	FragColor =  vec4(result_color, 1.0);
}


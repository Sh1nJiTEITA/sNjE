#version 330
out vec4 FragColor;

// Structs
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float shininess;
};

struct MaterialTex {
	sampler2D diffuse;
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
uniform MaterialTex material_tex;
uniform Light light;

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coo;

uniform vec3 view_pos;

void main()
{
	
	bool isTexture = true;

	if (isTexture) {
		// Ambient 
		vec3 ambient = light.ambient * texture(material_tex.diffuse, tex_coo).rgb;
	
		// Diffuse
		vec3 norm = normalize(normal);
		vec3 light_direction = normalize(light.position - frag_pos);

		float diff = max(dot(light_direction, norm), 0.0);
		vec3 diffuse = light.diffuse * diff * texture(material_tex.diffuse, tex_coo).rgb;

		// Specular
		vec3 view_direction = normalize(view_pos - frag_pos);
		vec3 reflect_direction = reflect(-light_direction, norm);

		float spec = pow(max(dot(view_direction, reflect_direction), 0.0001), material_tex.shininess);
		vec3 specular = light.specular * (spec * material_tex.specular);

		// Result
		vec3 result_color = ambient + diffuse + specular;

		FragColor =  vec4(result_color, 1.0);
	}
	else {
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
		
		// Result
		vec3 result_color = ambient + diffuse + specular;

		FragColor =  vec4(result_color, 1.0);
	}

	
}


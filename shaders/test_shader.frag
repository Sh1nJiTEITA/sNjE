#version 330

out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec2 tex;

struct Material
{
	sampler2D diffuse_1;
	sampler2D specular_1;
	sampler2D diffuse_2;
	sampler2D specular_2;
	sampler2D diffuse_3;
	sampler2D specular_3;
	sampler2D diffuse_4;
	sampler2D specular_4;
	sampler2D diffuse_5;
	sampler2D specular_5;

	float shininess;
};

uniform Material material;


void main()
{
	//FragColor = vec4(0.0, 1.0, 1.0, 1.0);
	//vec3 center = vec3(0.0, 0.0, 0.0);

	//vec3 color = (pos - center) * vec3(1.0, 1.0, 1.0);

	//FragColor = vec4(color, 1.0);
	FragColor = vec4(vec3(texture(material.diffuse_1, tex)), 1.0);
}
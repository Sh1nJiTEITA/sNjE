#version 330

out vec4 FragColor;

in vec3 pos;
in vec3 normal;
in vec2 tex;


void main()
{
	//FragColor = vec4(0.0, 1.0, 1.0, 1.0);
	vec3 center = vec3(0.0, 0.0, 0.0);

	vec3 color = (pos - center) * vec3(1.0, 1.0, 1.0);

	FragColor = vec4(color, 1.0);
}
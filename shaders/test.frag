#version 330
out vec4 FragColor;

//in vec3 color;

uniform vec3 model_color;
uniform vec3 light_color;

void main()
{
	//FragColor = vec4(color, 1.0);
	FragColor =  vec4(model_color * light_color, 1.0);
}


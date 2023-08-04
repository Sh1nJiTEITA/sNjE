#version 330

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

uniform mat4 projection;
uniform mat4 rot;
uniform mat4 view;

void main()
{
	//gl_Position = projection * view * vec4(aPos, 1.0);

	gl_Position = projection * view * rot * vec4(aPos, 1.0);

	//gl_Position = vec4(aPos, 1.0);
	//color = aColor;
}


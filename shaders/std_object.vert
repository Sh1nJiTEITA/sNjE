#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 projection;
uniform mat4 rot;
uniform mat4 view;

out vec3 normal;
out vec3 frag_pos;
out vec2 tex_coo;

void main()
{
	gl_Position = projection * view * rot * vec4(aPos, 1.0);

	frag_pos = vec3(rot * vec4(aPos, 1.0));
	tex_coo = aTex;

	// To fragment shader
	normal = aNormal;
}


#include "Shader.h"

Shader::Shader(std::string vert_shader_path, std::string frag_shader_path) :
	__vert_path(vert_shader_path),
	__frag_path(frag_shader_path)
{
	const std::string vert_shader = __readShader(__vert_path);
	const std::string frag_shader = __readShader(__frag_path);

	__activateShader(vert_shader.data(), frag_shader.data());
}

std::string Shader::__readShader(std::string path)
{
	std::stringstream rData;

	std::ifstream file;

	file.open(path);

	if (file.is_open()) {
		rData << file.rdbuf();
		
		file.close();
		return rData.str();
	}
	else
	{
		file.close();
		throw LocalException(
			"Shader file was not opened."
		);
	}
}

void Shader::__activateShader(const char* vert_source, const char* frag_source)
{
	/*
		0 - Vertex Shader;
		1 - Fragment Shader;
		2 - Shader program;
	*/
	
	// Create vertex shader
	unsigned int vert_id;
	
	vert_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_id, 1, &vert_source, NULL);
	glCompileShader(vert_id);
	
	// Check for problems in vertex shader
	__checkShaderForErrors(vert_id, 0);

	// Create fragment shader
	unsigned int frag_id;

	frag_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_id, 1, &frag_source, NULL);
	glCompileShader(frag_id);
	
	// Check for problems in fragment shader
	__checkShaderForErrors(vert_id, 0);

	// Create shader program
	__id = glCreateProgram();

	glAttachShader(__id, vert_id);
	glAttachShader(__id, frag_id);
	glLinkProgram(__id);
	
	// Check for problems in linking shader program
	__checkShaderForErrors(__id, 2);

	// Delete vertex and fragment shader parts
	glDeleteShader(vert_id);
	glDeleteShader(frag_id);
}

void Shader::__checkShaderForErrors(unsigned int shader_id, unsigned int shader_type)
{
	char info[512];
	int success;

	switch (shader_type) {
		case 0:
		case 1: {
			glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(shader_id, 512, NULL, info);
				std::stringstream ss;
				ss << "Exception in creating vert/frag shader: " << info << std::endl;
				throw LocalException(ss.str());
			}
		}
		case 2: {
			glGetProgramiv(shader_id, GL_LINK_STATUS, &success);

			if (!success) {
				glGetProgramInfoLog(shader_id, 512, NULL, info);
				std::stringstream ss;
				ss << "Exception in linking shader program: " << info << std::endl;
				throw LocalException(ss.str());
			}
		}

	}

}

void Shader::Use()
{
	glUseProgram(__id);
}

void Shader::SetVec2(const std::string& name, glm::vec2 inv)
{
	glUniform2fv(glGetUniformLocation(__id, name.c_str()), 1, &inv[0]);
}

void Shader::SetVec2(const std::string& name, float inv1, float inv2)
{
	glUniform2f(glGetUniformLocation(__id, name.c_str()), inv1, inv2);
}

void Shader::SetVec3(const std::string& name, glm::vec3 inv)
{
	glUniform3fv(glGetUniformLocation(__id, name.c_str()), 1, &inv[0]);
}

void Shader::SetVec3(const std::string& name, float inv1, float inv2, float inv3)
{
	glUniform3f(glGetUniformLocation(__id, name.c_str()), inv1, inv2, inv3);
}

void Shader::SetVec4(const std::string& name, glm::vec4 inv)
{
	glUniform4fv(glGetUniformLocation(__id, name.c_str()), 1, &inv[0]);
}

void Shader::SetVec4(const std::string& name, float inv1, float inv2, float inv3, float inv4)
{
	glUniform4f(glGetUniformLocation(__id, name.c_str()), inv1, inv2, inv3, inv4);
}

void Shader::SetBool(const std::string& name, bool inv)
{
	glUniform1i(glGetUniformLocation(__id, name.c_str()), (int)inv);
}

void Shader::SetFloat(const std::string& name, float inv)
{
	glUniform1f(glGetUniformLocation(__id, name.c_str()), inv);
}

void Shader::SetInt(const std::string& name, int inv)
{
	glUniform1i(glGetUniformLocation(__id, name.c_str()), inv);
}

void Shader::SetMat2(const std::string& name, glm::mat2 inv)
{
	glUniformMatrix2fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &inv[0][0]);
}

void Shader::SetMat3(const std::string& name, glm::mat3 inv)
{
	glUniformMatrix3fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &inv[0][0]);
}

void Shader::SetMat4(const std::string& name, glm::mat4 inv)
{
	glUniformMatrix4fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &inv[0][0]);
}

void Shader::SetModel(glm::mat4 inv)
{
	this->SetMat4("model", inv);
}

void Shader::SetProjection(glm::mat4 inv)
{
	this->SetMat4("projection", inv);
}

void Shader::SetView(glm::mat4 inv)
{
	this->SetMat4("view", inv);
}

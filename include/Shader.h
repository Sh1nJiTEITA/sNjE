/*
	Shader class.

	This class provides opportunity to work with shaders - 
	small programs, which handles the graphics behaviour.

	Time creation: 01.08.2023

	Auther: sNj
*/


#ifndef SHADER_H
#define SHADER_H
// external libraries //

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>


// STL libraries // 
#include <string>
#include <fstream>
#include <sstream>

// Local libraries // 
#include <LocalException.hpp>

class Shader
{
	std::string __vert_path;
	std::string __frag_path;

	unsigned int __id;
	
	// Returns string data from input file
	std::string __readShader(std::string path);

	// Activates shader in OpenGL order
	void __activateShader(const char* vert_source, const char* frag_source);

	// Checks if input shader is generated properly
	void __checkShaderForErrors(unsigned int shader_id, unsigned int shader_type);

public:
	Shader(std::string vert_shader_path, std::string frag_shader_path);
	// Uses this shader for OpenGL
	void Use();
	
	/* Setters */
	void SetVec2(const std::string& name, glm::vec2 inv);
	void SetVec2(const std::string& name, float inv1, float inv2);
	void SetVec3(const std::string& name, glm::vec3 inv);
	void SetVec3(const std::string& name, float inv1, float inv2, float inv3);
	void SetVec4(const std::string& name, glm::vec4 inv);
	void SetVec4(const std::string& name, float inv1, float inv2, float inv3, float inv4);

	void SetBool(const std::string& name, bool inv);
	void SetFloat(const std::string& name, float inv);
	void SetInt(const std::string& name, int inv);

	void SetMat2(const std::string& name, glm::mat2 inv);
	void SetMat3(const std::string& name, glm::mat3 inv);
	void SetMat4(const std::string& name, glm::mat4 inv);

	void SetModel(glm::mat4 inv);
	void SetProjection(glm::mat4 inv);
	void SetView(glm::mat4 inv);
};


#endif
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
	
public:
	Shader(std::string vert_shader_path, std::string frag_shader_path);
		
	// Returns string data from input file
	std::string __readShader(std::string path);

	// Activates shader in OpenGL order
	void __activateShader(const char* vert_source, const char* frag_source);

	// Checks if input shader is generated properly
	void __checkShaderForErrors(unsigned int shader_id, unsigned int shader_type);

	// Uses this shader for OpenGL
	void use();
};


#endif
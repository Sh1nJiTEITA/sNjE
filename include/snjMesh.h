/*
*	Class provides working with meshes.
*
*
*	Date: 08.08.2023
*	Creator: sNj
*
*/


#ifndef SNJMESH_H
#define SNJMESH_H

// Libraries //

// External
#include <glad/glad.h>

// Local
#include <snjVertex.h>
#include <LocalException.hpp>
#include <Shader.h>

// STL
#include <vector>
#include <string>
//#include <algorithm>
#include <unordered_map>

// Defines
#define SNJ_DIFFUSE_TEXTURE 0x01
#define SNJ_SPECULAR_TEXTURE 0x02

// 






struct snjTexture {


	unsigned int id;
	std::string path;
	unsigned int type;
	
	
	snjTexture(std::string _path, unsigned int _type, unsigned int _id) : path(_path), type(_type), id(_id)
	{	
	}
};




class snjMesh {

	std::vector<snjVertex> __vertices;
	std::vector<unsigned int> __indices;
	std::vector<snjTexture> __textures;

	unsigned int __VAO, __VBO, __EBO;

	bool __is_pos;
	bool __is_normal;
	bool __is_texture_coo;
	
	float __shininess;

	unsigned int __stride;

	void __setUpData();
	
	/*
	* Checks how input data was provided.
	* 
	* 
	* 
	* 
	*/
	
	void __checkData();

public:

	snjMesh(std::vector<snjVertex> vertices, std::vector<unsigned int> indices, std::vector<snjTexture> textures);
	snjMesh(std::vector<snjVertex> vertices, std::vector<unsigned int> indices, std::vector<snjTexture> textures, float _sh);


	//void SimplifyIndices();
	void draw(Shader shader);

};



#endif
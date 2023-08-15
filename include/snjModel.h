#ifndef SNJMODEL_H
#define SNJMODEL_H


// Libraries //
// External
#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Local
#include <snjMesh.h>
#include <LocalException.hpp>

// STL
#include <string>
#include <algorithm>


class snjModel
{
	std::vector<snjMesh> __meshes;
	std::vector<snjTexture> __loaded_textures;


	// Root path of directory
	std::string __path;

	void __setUpData();
	
	bool __isTextureLoaded(const char* name);

	void __processNode(aiNode* node, const aiScene* scene);
	snjMesh __processMesh(aiMesh* mesh, const aiScene* scene);
	unsigned int __textureFromFile(const char* path);
	std::vector<snjTexture> __loadMeterialTextures(aiMaterial* mat, aiTextureType aitype, unsigned int type);

public:
	snjModel(const char* path);
	
	void draw(Shader& shader);









};



#endif

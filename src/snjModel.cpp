#include "snjModel.h"

void snjModel::__setUpData()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		__path, 
		aiProcess_Triangulate | 
		aiProcess_GenSmoothNormals | 
		aiProcess_FlipUVs
	);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::stringstream ss;
		ss << "Error with loading model (Assimp):" << importer.GetErrorString() << std::endl;
		
		throw LocalException(ss.str());
	}

	__processNode(scene->mRootNode, scene);
}

//bool snjModel::__isTextureLoaded(const char* name)
//{
//	if (std::any_of(
//		__loaded_textures.begin(),
//		__loaded_textures.end(),
//		[&](snjTexture tex) { tex.path.c_str() == name; }
//	))
//		return true;
//	else
//		return false;
//}

void snjModel::__processNode(aiNode* node, const aiScene* scene)
{
	unsigned int mesh_num = node->mNumMeshes;

 	for (size_t mesh_index = 0; mesh_index < mesh_num; ++mesh_index)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[mesh_index]];
		__meshes.push_back(__processMesh(mesh, scene));
	}

	unsigned int ch_num = node->mNumChildren;

	for (size_t ch_index = 0; ch_index < ch_num; ++ch_index)
	{
		__processNode(node->mChildren[ch_index], scene);
	}

}

snjMesh snjModel::__processMesh(aiMesh* mesh, const aiScene* scene)
{
	/* 
	* aiMesh: 
	*	~Always
	*	1. Positions 
	*	2. Normals
	*	3. Texture coordinates
	*
	*	4. Textures	
	* 
	*	~Sometimes
	*	5. Vertex colors
	*	6. Bones TODO
	*/

  	unsigned int vertices_num = mesh->mNumVertices;
	unsigned int face_num = mesh->mNumFaces;

	std::vector<snjVertex> vertices(vertices_num);
	std::vector<unsigned int> indices(face_num * 3);
	std::vector<snjTexture> textures;

	if (!mesh->HasNormals())
	{
		std::stringstream ss;
		ss << "Error in loading model. Model with path: '" << this->__path 
			<< "' consists of Mesh '" << mesh->mName.C_Str() 
			<< "', which has no normals." << std::endl;
		throw LocalException(ss.str());
	}

	if (!mesh->HasFaces())
	{
		std::stringstream ss;
		ss << "Error in loading model. Model with path: '" << this->__path
			<< "' consists of Mesh '" << mesh->mName.C_Str()
			<< "', which has no faces (indices)." << std::endl;
		throw LocalException(ss.str());
	}

	bool isTexture = true;
	if (!mesh->HasTextureCoords(0))
	{
		std::stringstream ss;
		ss << "Error in loading model. Model with path: '" << this->__path
			<< "' consists of Mesh '" << mesh->mName.C_Str()
			<< "', which has no texture coordinates." << std::endl;
		std::cout << ss.str() << std::endl;
		//throw LocalException(ss.str());
		isTexture = false;
	}
	
	


	for (size_t vertex_index = 0; vertex_index < vertices_num; ++vertex_index)
	{
		
		if (isTexture)
		{
			snjVertex vert(
				mesh->mVertices[vertex_index],
				mesh->mNormals[vertex_index],
				mesh->mTextureCoords[0][vertex_index]
			);
			vertices[vertex_index] = vert;
		}
		else
		{
			snjVertex vert(
				mesh->mVertices[vertex_index],
				mesh->mNormals[vertex_index],
				aiVector3D(SNJ_NAN, SNJ_NAN, SNJ_NAN)
			);
			vertices[vertex_index] = vert;
		}
	}
	
	unsigned int index_num = mesh->mFaces->mNumIndices;

	for (size_t face_index = 0; face_index < face_num; ++face_index)
	{
		for (size_t index_index = 0; index_index < index_num; ++index_index)
		{
			indices[face_index * 3 + index_index] = mesh->mFaces[face_index].mIndices[index_index];
		}
	}

	// Material and textures //
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


	float sh;
	if (AI_SUCCESS != material->Get(AI_MATKEY_SHININESS, sh)) {
		
		std::cout << "Now shininess in model: " << mesh->mName.C_Str() << std::endl;
	}
	else
	{
		std::cout << "Shininess of " << mesh->mName.C_Str() << "is "<< sh << std::endl;
	}

	if (isTexture)
	{
		// Diffuse
		std::vector<snjTexture> diffuse_textures = __loadMeterialTextures(material, aiTextureType_DIFFUSE, SNJ_DIFFUSE_TEXTURE);
		textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());

		// Specular
		std::vector<snjTexture> specular_textures = __loadMeterialTextures(material, aiTextureType_SPECULAR, SNJ_SPECULAR_TEXTURE);
		textures.insert(textures.end(), specular_textures.begin(), specular_textures.end());
	}
	
	return snjMesh(vertices, indices, textures);
}

unsigned int snjModel::__textureFromFile(const char* path)
{
	std::string file(path);

	unsigned int texture_id;
	glGenTextures(1, &texture_id);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		std::cout << "Texture was loaded with path: " << path << std::endl;
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		std::stringstream ss;
		ss << "Error in snjModel.cpp::loadTexture: Texture loading was't successful: input path is:";
		ss << file << std::endl;
		stbi_image_free(data);
		
		std::cout << ss.str() << std::endl;
		//throw LocalException(ss.str());
	}

	return texture_id;

}

std::vector<snjTexture> snjModel::__loadMeterialTextures(aiMaterial* mat, aiTextureType aitype, unsigned int type)
{
	std::vector<snjTexture> textures;
	
	unsigned int texture_num = mat->GetTextureCount(aitype);

	aiString texture_name;

	for (int texture_index = 0; texture_index < texture_num; ++texture_index)
	{
		mat->GetTexture(aitype, texture_index, &texture_name);
		
		std::string texture_name_ = std::string(texture_name.C_Str());
		// If String contains "\" instead of "/"
		if (texture_name_.find('\\') != std::string::npos)
		{
			std::replace(texture_name_.begin(), texture_name_.end(), '\\', '/');
		}
		
		
		// Cut main texture name:
		size_t texture_name_pos = texture_name_.find_last_of('/');

		if (texture_name_pos != std::string::npos)
		{
			texture_name_ = texture_name_.substr(texture_name_pos + 1, texture_name_.size());
		}

		std::string path_to_texture = this->__path;
		size_t slash_pos = path_to_texture.find_last_of("/");

		if (slash_pos != std::string::npos)
		{
			path_to_texture = path_to_texture.substr(0, slash_pos + 1);
			path_to_texture.append(texture_name_);
		}
		else 
		{
			throw LocalException("No texture with such name was founded.");
		}

		bool is_texture_was_loaded = false;
		// Check if texture is loaded
		for (int texture_index = 0; texture_index < __loaded_textures.size(); ++texture_index)
		{
			if (path_to_texture == __loaded_textures[texture_index].path)
			{
				textures.push_back(__loaded_textures[texture_index]);
				is_texture_was_loaded = true;
				break;
			}
		}
		if (!is_texture_was_loaded)
		{
      		unsigned int new_texture_id = __textureFromFile(path_to_texture.c_str());
			//unsigned int new_texture_id = __textureFromFile(texture_name.C_Str());
			snjTexture new_texture(path_to_texture, type, new_texture_id);

			__loaded_textures.push_back(new_texture);
			textures.push_back(new_texture);
		}
	}

	
	return textures;
}

snjModel::snjModel(const char* path) :
	__path(path),
	__pos(glm::vec3(1.0f))
{
	__setUpData();
}

snjModel::snjModel(const char* path, glm::vec3 pos) :
	__path(path),
	__pos(pos)
{
	__setUpData();
}



void snjModel::ChangePosByVec3(glm::vec3 pos_vec)
{
	__pos = pos_vec;
}

void snjModel::draw(Shader& shader)
{
	this->drawm(shader);
}

void snjModel::drawm(Shader& shader)
{
	// Set model position in 3D space
	shader.SetMat4("model", glm::translate(glm::mat4(1.0f), __pos));

	for (size_t mesh_index = 0; mesh_index < __meshes.size(); ++mesh_index)
	{
		__meshes[mesh_index].draw(shader);
	}
}

#include "snjMesh.h"

void snjMesh::__setUpData()
{
	__checkData();


	glGenVertexArrays(1, &__VAO);
	glGenBuffers(1, &__VBO);
	glGenBuffers(1, &__EBO);
	

	glBindVertexArray(__VAO);
	glBindBuffer(GL_ARRAY_BUFFER, __VBO);
	
	// Check if all 
	
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(snjVertex) * __vertices.size(), 
		__vertices.data(), 
		GL_STATIC_DRAW
	);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, __EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		__indices.size() * sizeof(unsigned int),
		__indices.data(),
		GL_STATIC_DRAW
	);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	unsigned int stride = 0;

	if (__is_pos)
	{
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(snjVertex), (void*)(stride));
		glEnableVertexAttribArray(0);
		stride += 3;
	}
	if (__is_normal)
	{
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(snjVertex), (void*)(stride * sizeof(float)));
		glEnableVertexAttribArray(1);
		stride += 3;
	}
	if (__is_texture_coo)
	{
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(snjVertex), (void*)(stride * sizeof(float)));
		glEnableVertexAttribArray(2);
		stride += 2;
	}


	

	//glBindVertexArray(0);
}


void snjMesh::__checkData()
{
	if (__vertices.empty())
	{
		throw LocalException("Error::snjMesh: Vertices array is empty.");
	}
	if (__indices.empty())
	{
		throw LocalException("Error::snjMesh: Indices array is empty.");
	}
	

	if (!std::any_of(__vertices.begin(), __vertices.end(), [](snjVertex vert) { return vert.isPos(); }))
	{
		if (std::all_of(__vertices.begin(), __vertices.end(), [](snjVertex vert) { return !vert.isPos(); }))
		{
			throw LocalException("Error::snjMesh: No vertices position data was defined.");
		}
		else
		{
			throw LocalException("Error::snjMesh: Not all vertices position is defined.");
		}
	}
	

	if (!std::any_of(__vertices.begin(), __vertices.end(), [](snjVertex vert) { return vert.isNorm(); }))
	{
		if (!std::all_of(__vertices.begin(), __vertices.end(), [](snjVertex vert) { return vert.isNorm(); }))
		{
			throw LocalException("Error::snjMesh: No vertices normal data was defined.");
		}
		else 
		{
			throw LocalException("Error::snjMesh: Not all vertices normal is defined.");
		}
	}

	// TODO: Texture adaptation;
	/*if (!std::all_of(__vertices.begin(), __vertices.end(), [](snjVertex vert) { return vert.isTex(); }))
	{
		throw LocalException("Error::snjMesh: Not all vertices texture coordinates is defined");
	}*/

}

snjMesh::snjMesh(std::vector<snjVertex> vertices, std::vector<unsigned int> indices, std::vector<snjTexture> textures) :
	__vertices(vertices),
	__indices(indices),
	__textures(textures)
{
	__setUpData();
}


void snjMesh::draw(Shader shader)
{
 	shader.Use();

	unsigned int diff_counter = 1;
	unsigned int spec_counter = 1;

	for (unsigned int texture_index = 0; texture_index < __textures.size(); ++texture_index)
	{
		glActiveTexture(GL_TEXTURE0 + texture_index);

		std::string texture_type;

		if (__textures[texture_index].type == SNJ_DIFFUSE_TEXTURE)
		{
			texture_type = "diffuse_" + std::to_string(diff_counter);
			diff_counter++;
		}
		else if (__textures[texture_index].type == SNJ_SPECULAR_TEXTURE)
		{
			texture_type = "specular_" + std::to_string(spec_counter);
			spec_counter++;
		}
		else
		{
			throw LocalException("Error in mesh: Underfined type of texture");
		}
		glActiveTexture(GL_TEXTURE0);
		std::string variable = "material." + texture_type;

		shader.SetInt(variable, texture_index);
		glBindTexture(GL_TEXTURE_2D, __textures[texture_index].id);

	}


	glBindVertexArray(__VAO);
	glDrawElements(GL_TRIANGLES, __indices.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}

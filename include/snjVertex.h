/*	
*	Class provides working with vertices.
* 
* 
*	Date: 07.08.2023	
*	Creator: sNj
* 
*/


#ifndef snjVertexr_H
#define snjVertexr_H

// // Libraries 

// External
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
// Local

// Stl
#include <vector>
#include <cmath>
#include <array>
#include <algorithm>
#include <iostream>
#include <assimp/vector3.h>

#define SNJ_NAN std::nan("sNaN")

class snjVertexr
{
public:
	// Variables //

	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tcoo;
	
	float& x;
	float& y;
	float& z;
	
	float& nx;
	float& ny;
	float& nz;

	float& s;
	float& t;

	// Constructors //

	snjVertexr();
	snjVertexr(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _s, float _t);
	snjVertexr(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _tcoor);
	snjVertexr(aiVector3D _pos, aiVector3D _norm, aiVector3D _tcoor);

	// Methods //
	bool isPos();
	bool isNorm();
	bool isTex();

	unsigned int CalcStride();
	
	
	// Overload //

	

	friend std::ostream& operator<<(std::ostream& os, const snjVertexr& vertex) noexcept;

};

class snjVertex
{
public:
	// Variables //

	glm::vec3 pos;
	glm::vec3 nor;
	glm::vec2 tex;

	// Constructors //

	snjVertex();
	snjVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _s, float _t);
	snjVertex(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _tcoor);
	snjVertex(aiVector3D _pos, aiVector3D _norm, aiVector3D _tcoor);

	// Methods //
	bool isPos();
	bool isNorm();
	bool isTex();

	unsigned int CalcStride();


	// Overload //
	bool operator==(const snjVertex& vertex) const;
	friend std::ostream& operator<<(std::ostream& os, const snjVertex& vertex) noexcept;

};



#endif
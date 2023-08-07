/*	
*	Class provides working with vertices.
* 
* 
*	Date: 07.08.2023	
*	Creator: sNj
* 
*/


#ifndef SNJVERTEX_H
#define SNJVERTEX_H

// // Libraries 

// External
#include <glm/vec3.hpp>

// Local

// Stl
#include <vector>
#include <cmath>
#include <array>
#include <algorithm>
#include <iostream>
#include <assimp/vector3.h>

#define SNJ_NAN std::nan("sNaN")

class snjVertex
{
	std::array<float, 3> __data;

public:
	// Variables //
	
	float& x;
	float& y;
	float& z;
	 
	// Constructors //

	snjVertex();
	snjVertex(float _x, float _y, float _z);
	snjVertex(glm::vec3 vec);
	snjVertex(aiVector3D vec);

	// Methods //
	bool isFilled();
	float* ptr_pack();
	
	// Overload //

	friend std::ostream& operator<<(std::ostream& os, const snjVertex& vertex);

};





#endif
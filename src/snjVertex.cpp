#include "snjVertex.h"



snjVertex::snjVertex(float _x, float _y, float _z) :
	__data{ _x, _y, _z },
	x(__data[0]),
	y(__data[1]),
	z(__data[2]) {}

snjVertex::snjVertex() : snjVertex(SNJ_NAN, SNJ_NAN, SNJ_NAN) {}
snjVertex::snjVertex(glm::vec3 vec) : snjVertex(vec.x, vec.y, vec.z) {}
snjVertex::snjVertex(aiVector3D vec) : snjVertex(vec.x, vec.y, vec.z) {}


bool snjVertex::isFilled()
{
	if (std::any_of(__data.begin(), __data.end(), [](float i){return std::isnan(i);}))
		return false;
	else
		return true;
}

float* snjVertex::ptr_pack()
{
	return __data.data();
}

std::ostream& operator<<(std::ostream& os, const snjVertex& vertex)
{
	os << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")";
	return os;
}

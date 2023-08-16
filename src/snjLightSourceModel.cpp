#include "snjLightSourceModel.h"


snjLightSourceProperty::snjLightSourceProperty(unsigned int mode) :
	ambient(glm::vec3(0.05f, 0.05f, 0.05f)),
	diffuse(glm::vec3(0.8f, 0.8f, 0.8f)),
	specular(glm::vec3(1.0f, 1.0f, 1.0f)),

	constant(1.0f),
	linear(0.09f),
	quadratic(0.032f)
{}

snjLightSourceModel::snjLightSourceModel(const char* path, unsigned int mode, glm::vec3 pos) :
	snjModel(path, pos),
	__lp(snjLightSourceProperty(mode))
	

{
}

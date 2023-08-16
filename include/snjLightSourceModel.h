
/*
*	Class provides working with light sources.
*
*
*	Date: 15.08.2023
*	Creator: sNj
*
*/

#ifndef SNJLIGHTSOURCEMODEL_H
#define SNJLIGHTSOURCEMODEL_H

// Libraries 

// External //
#include <glm/gtx/transform.hpp>


// Local //
#include <snjModel.h>


// STL //

/*
 * Each snjLightSourceModel contains model (which could be loaded as usual model),
 * and some light properties:
 * 
 * vec3 position - tells where model is located;
 * 
 * vec3 ambient  }
 * vec3 diffuse  } - Color constants 
 * vec3 specular }
 * 
 * float constant  }
 * float linear	   } - Light properties, manages how far light could matter;
 * float quadratic } 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#define SNJ_USUAL_LS 0x0000001

struct snjLightSourceProperty {

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	snjLightSourceProperty(unsigned int mode);
};



class snjLightSourceModel : public snjModel
{
	snjLightSourceProperty __lp;

	
public:
	snjLightSourceModel(
		const char* path,
		unsigned int mode = SNJ_USUAL_LS,
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f)
	);
};





#endif
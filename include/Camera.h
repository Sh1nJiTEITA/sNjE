/*
	Camera class.

	File contains different types of camera.

	Time creation: 02.08.2023

	Auther: sNj
*/


#ifndef CAMERA_H
#define CAMERA_H
// External //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
// STL //

// Local //



/*
	Class provides free flying camera for
	debugging.
*/
class CameraBase
{
protected:

	// Projection part
	float __fov;
	float __near_plane;
	float __far_plane;
	
	// View part
	unsigned int* __window_width;
	unsigned int* __window_height;
	
	glm::vec3 __pos;
	glm::vec3 __front;
	glm::vec3 __up;

	double __last_frame_time;
	double __delta_time;

public:
	CameraBase(
		glm::vec3 pos,
		glm::vec3 front, 
		glm::vec3 up, 
		unsigned int* wid, 
		unsigned int* hei
	);
	CameraBase();

	glm::mat4 GetView();
	glm::mat4 GetProjection();

	// Delta time 
	void UpdateDeltaTime();
	const double GetDeltaTime();
};

class FreeFlightCamera : public CameraBase
{
	
public:
	FreeFlightCamera(
		glm::vec3 pos,
		glm::vec3 front,
		glm::vec3 up,
		unsigned int* wid,
		unsigned int* hei
	);


};




#endif
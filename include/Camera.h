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
#include <iostream>

// Local //
#include <LocalException.hpp>


/*
	Class provides free flying camera for
	debugging.
*/
class CameraBase
{
protected:
	// Mouse parts
	float* __m_x_pos;
	float* __m_y_pos;

	// Projection part
	float __fov;
	float __near_plane;
	float __far_plane;
	
	// View part
	unsigned int* __window_width;
	unsigned int* __window_height;
	
	
	double __last_frame_time;
	double __delta_time;

	

public:

	// For public use:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	
	float speed;

	

	CameraBase(
		glm::vec3 _pos,
		glm::vec3 _front, 
		glm::vec3 _up, 
		unsigned int* _wid, 
		unsigned int* _hei
	);
	CameraBase();


	glm::mat4 GetView();
	glm::mat4 GetProjection();

	// Delta time 
	void UpdateDeltaTime();
	const double GetDeltaTime();

	void BindMousePos(float* x_pos, float* y_pos);
	void UnbindMousePos();
	
};




class FreeFlightCamera : public CameraBase
{
	float __last_xpos;
	float __last_ypos;

	float __yaw;
	float __pitch;

public:
	FreeFlightCamera(
		glm::vec3 pos,
		glm::vec3 front,
		glm::vec3 up,
		unsigned int* wid,
		unsigned int* hei
	);

	void GoStraight();
	void GoBack();
	void GoRight();
	void GoLeft();
	void GoUp();
	void GoDown();

	void UpdateMouse();
};




#endif
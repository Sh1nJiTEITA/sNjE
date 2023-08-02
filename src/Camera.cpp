#include "Camera.h"

CameraBase::CameraBase(
	glm::vec3 pos,
	glm::vec3 front,
	glm::vec3 up,
	unsigned int* wid,
	unsigned int* hei
) :
	__pos(pos),
	__front(front),
	__up(up),
	__window_width(wid),
	__window_height(hei),
	// Standart Values
	__last_frame_time(0.0f),
	__delta_time(0.0f),
	__fov(glm::radians(45.0f)),
	__near_plane(0.1f),
	__far_plane(100.0f)
{}

CameraBase::CameraBase()
{
	CameraBase(
		glm::vec3(0.0f, 0.0f, 0.3f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		nullptr,
		nullptr
	);
}

glm::mat4 CameraBase::GetView()
{
	return glm::lookAt(__pos, __pos + __front, __up);
}

glm::mat4 CameraBase::GetProjection()
{
	return glm::perspective(
		__fov,
		(float)(*__window_width / *__window_height),
		__near_plane,
		__far_plane
	);
}

void CameraBase::UpdateDeltaTime()
{
	double this_frame_time = glfwGetTime();
	__delta_time = this_frame_time - __last_frame_time;
	__last_frame_time = this_frame_time;
}

const double CameraBase::GetDeltaTime()
{
	return __delta_time;
}

// Free Flight Camera //


FreeFlightCamera::FreeFlightCamera(
	glm::vec3 pos, 
	glm::vec3 front, 
	glm::vec3 up, 
	unsigned int* wid, 
	unsigned int* hei) : 
	
	CameraBase(
		pos,
		front,
		up,
		wid,
		hei
	)
{
{
}


}
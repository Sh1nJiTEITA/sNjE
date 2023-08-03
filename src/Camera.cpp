#include "Camera.h"

CameraBase::CameraBase(
	glm::vec3 _pos,
	glm::vec3 _front,
	glm::vec3 _up,
	unsigned int* _wid,
	unsigned int* _hei
) :
	pos(_pos),
	front(_front),
	up(_up),
	speed(2.5f),
	
	__window_width(_wid),
	__window_height(_hei),
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
	return glm::lookAt(this->pos, this->pos + this->front, this->up);
}

glm::mat4 CameraBase::GetProjection()
{
	return glm::perspective(
		__fov,
		((float) * __window_width) / ((float) * __window_height),
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

void FreeFlightCamera::GoStraight()
{
	this->pos += this->speed * (float)__delta_time * this->front;
}

void FreeFlightCamera::GoBack()
{
	this->pos -= this->speed * (float)__delta_time * this->front;
}

void FreeFlightCamera::GoRight()
{
	this->pos += this->speed * glm::normalize(glm::cross(this->front, this->up)) * (float)__delta_time;
}

void FreeFlightCamera::GoLeft()
{
	this->pos -= this->speed * glm::normalize(glm::cross(this->front, this->up)) * (float)__delta_time;
}

void FreeFlightCamera::GoUp()
{
	this->pos += this->speed * glm::vec3(0.0f, 1.0f, 0.0f) * (float)__delta_time;
}

void FreeFlightCamera::GoDown()
{
	this->pos -= this->speed * glm::vec3(0.0f, 1.0f, 0.0f) * (float)__delta_time;
}

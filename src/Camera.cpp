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
	__far_plane(100.0f),
	__m_x_pos(nullptr),
	__m_y_pos(nullptr)
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

void CameraBase::BindMousePos(float* x_pos, float* y_pos)
{
	bool exc_x = false;
	bool exc_y = false;

	if (__m_x_pos == nullptr)
		__m_x_pos = x_pos;
	else
		exc_x = true;
	if (__m_y_pos == nullptr)
		__m_y_pos = y_pos;
	else
		exc_y = true;

	if (exc_x || exc_x)
	{
		std::stringstream ss;
		
		ss << "Local Exception. Some mouse has already been bound: ";
		if (exc_x)
			ss << "x_pos to " << __m_x_pos << " ";
		if (exc_y)
			ss << "y_pos to " << __m_y_pos << " ";

		ss << std::endl;

		throw LocalException(ss.str());
	}

}

void CameraBase::UnbindMousePos()
{
	__m_x_pos = nullptr;
	__m_y_pos = nullptr;
}



// Free Flight Camera //


FreeFlightCamera::FreeFlightCamera(
	glm::vec3 pos,
	glm::vec3 front,
	glm::vec3 up,
	unsigned int* wid,
	unsigned int* hei) :

	__yaw(0),
	__pitch(0),
	__last_xpos(0),
	__last_ypos(0),

	CameraBase(
		pos,
		front,
		up,
		wid,
		hei
	)
{}

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

void FreeFlightCamera::UpdateMouse()
{
	if ((__m_x_pos == nullptr) || (__m_y_pos == nullptr))
		return;
	
	/*float sensitivity = 0.1;

	float width = *__window_width;
	float height = *__window_height;

	float xpos = *__m_x_pos - width / 2; xpos *= sensitivity;
	float ypos = *__m_y_pos - height / 2; ypos *= sensitivity;

	float rad_x_angle = -glm::pi<float>() * 2 * xpos / width;
	float rad_y_angle = -glm::pi<float>() * ypos / height;
	
	if (glm::degrees(rad_y_angle) > 89.9f)
	{
		rad_y_angle = glm::radians(89.0f);
	}

	if (glm::degrees(rad_y_angle) < -89.9f)
		rad_y_angle = glm::radians(-89.0f);
	
	this->front = glm::vec3(
		glm::sin(rad_x_angle) * cos(rad_y_angle), 
		glm::sin(rad_y_angle),
		glm::cos(rad_x_angle) * cos(rad_y_angle)
	);
	this->front = glm::normalize(this->front);*/
	float sensitivity = 0.1;

	float xpos_new = *__m_x_pos;
	float ypos_new = *__m_y_pos;

	float xoffset = (xpos_new - __last_xpos) * sensitivity;
	float yoffset = (__last_ypos - ypos_new) * sensitivity;

	__last_xpos = xpos_new;
	__last_ypos = ypos_new;

	__yaw += xoffset;
	__pitch += yoffset;

	if (__pitch > 89.0f)
		__pitch = 89.0f;
	if (__pitch < -89.0f)
		__pitch = -89.0f;

	front = glm::normalize(glm::vec3(
		glm::cos(glm::radians(__yaw)) * glm::cos(glm::radians(__pitch)),
		glm::sin(glm::radians(__pitch)),
		glm::sin(glm::radians(__yaw)) * glm::cos(glm::radians(__pitch))
	));  

	//std::cout << "(" << xpos << ", " << ypos << ")";
	std::cout << "\t(" << front.x << ", " << front.y << ", " << front.z << ")";
	std::cout << "\t angle(x/z: " << glm::degrees(__yaw) << ", y:" << glm::degrees(__pitch) << ") " << std::endl;
}

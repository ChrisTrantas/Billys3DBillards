#include "Camera.h"


Camera::Camera()
{
	Init();

	CalculateView();
	CalculateProjection();
}

void Camera::Init()
{
	m_v3Position = vector3(0);
	m_v3Orientation = vector3(0);

	m_bOrthogonal = false;
	m_b6DoF = false;

	m_v3Up = vector3(0, 1.0f, 0);
	m_v3Forward = vector3(-1.0f, 0, 0);

	m_fFOVy = 45.0f;

	m_fAspectRatio = SystemSingleton::GetInstance()->GetWindowRatio();
	m_fMinPlane = 0.001f;
	m_fMaxPlane = 100.0f;
	m_fHeight = SystemSingleton::GetInstance()->GetWindowHeight();

	CalculateDirectionVectors();
	CalculateView();
	CalculateProjection();
}

Camera::~Camera(){}

void Camera::CalculateView()
{
	m_m4View = glm::lookAt(m_v3Position, m_v3Position + m_v3Forward, m_v3Up);
}

void Camera::CalculateProjection()
{
	if (m_bOrthogonal)
	{
		float fHalfHeight = m_fHeight / 2;
		m_m4Projection = 
			glm::ortho(
				-fHalfHeight * m_fAspectRatio,	// Left
				fHalfHeight * m_fAspectRatio,	// Right
				-fHalfHeight,					// Bottom
				fHalfHeight,					// Top
				m_fMinPlane,					// Min Plane
				m_fMaxPlane						// Far Plane
			);
	}
	else
	{
		m_m4Projection = glm::perspective(m_fFOVy, m_fAspectRatio, m_fMinPlane, m_fMaxPlane);
	}
}

// Calculates the Up, Forward, and Rigth vectors from the orientation.
void Camera::CalculateDirectionVectors()
{
	m_v3Right = glm::cross(m_v3Forward, m_v3Up);

	// Compute quaternion for pitch based on the camera pitch angle
	quaternion qPitch = glm::angleAxis(m_v3Orientation.x, m_v3Right);
	// Compute quaternion for Yaw based on the camera pitch angle
	quaternion qYaw = glm::angleAxis(m_v3Orientation.y, m_v3Up);
	//Compute quaternion for Roll based on the camera pitch angle
	quaternion qRoll = glm::angleAxis(m_v3Orientation.z, m_v3Forward);

	//Add the quaternions
	quaternion qTemp = qPitch * qYaw;

	m_v3Forward = glm::rotate(qTemp, m_v3Forward);

	// Changes the Up and Right vector if Six Degrees of Freedom is set.
	if (m_b6DoF)
	{
		qTemp = glm::cross(qRoll, qPitch);
		m_v3Up = glm::rotate(qTemp, m_v3Up);

		qTemp = glm::cross(qYaw, qRoll);
		m_v3Right = glm::rotate(qTemp, m_v3Right);
	}

	m_v3Forward = glm::normalize(m_v3Forward);
	m_v3Up = glm::normalize(m_v3Up);
	m_v3Right = glm::normalize(m_v3Right);
}

matrix4 Camera::GetView()
{
	return m_m4View;
}
matrix4 Camera::GetProjection()
{
	return m_m4Projection;
}

void Camera::LookAtDirection(vector3 a_v3Direction)
{
	// Makes sure the new direction vector actually points somewhere.
	if (a_v3Direction.length() != 0)
	{
		m_v3Forward = a_v3Direction;

		CalculateView();
	}
}
void Camera::LookAtPosition(vector3 a_v3Target)
{
	// Makes sure the new target location is not the current location
	if (a_v3Target != m_v3Position)
	{
		m_v3Forward = a_v3Target - m_v3Position;

		CalculateView();
	}
}

vector3 Camera::GetPosition()
{
	return m_v3Position;
}
void Camera::SetPosition(vector3 a_v3Position)
{
	m_v3Position = a_v3Position;
	CalculateView();
}

vector3 Camera::GetOrientation()
{
	return m_v3Orientation;
}
void Camera::SetOrientation(vector3 a_v3Orientation)
{
	m_v3Orientation = a_v3Orientation;

	CalculateDirectionVectors();
	CalculateView();
}

vector3 Camera::GetUp()
{
	return m_v3Up;
}
void Camera::SetUp(vector3 a_v3Up)
{
	m_v3Up = a_v3Up;
}

vector3 Camera::GetForward()
{
	return m_v3Forward;
}
void Camera::SetForward(vector3 a_v3Forward)
{
	m_v3Forward = a_v3Forward;
}

// Move Camera
void Camera::MoveForward(float a_fIncrement)
{
	m_v3Position += m_v3Forward * a_fIncrement;
	CalculateView();
}
void Camera::MoveRight(float a_fIncrement)
{
	m_v3Position += m_v3Right * a_fIncrement;
	CalculateView();
}
void Camera::MoveUp(float a_fIncrement)
{
	m_v3Position += m_v3Up * a_fIncrement;
	CalculateView();
}

// Rotate Camera
void Camera::ChangePitch(float a_fIncrement)
{
	m_v3Orientation.x = a_fIncrement;
	
	CalculateDirectionVectors();
	CalculateView();
}
void Camera::ChangeYaw(float a_fIncrement)
{
	m_v3Orientation.y = a_fIncrement;
	
	CalculateDirectionVectors();
	CalculateView();
}
void Camera::ChangeRoll(float a_fIncrement)
{
	m_v3Orientation.z = a_fIncrement;
	
	CalculateDirectionVectors();
	CalculateView();
}
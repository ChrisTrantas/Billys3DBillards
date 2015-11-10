#include "Camera.h"

Camera::Camera(GameObject* gameObject)
	: Component(gameObject)
{
	Init();

	CalculateView();
	CalculateProjection();
}

void Camera::Init()
{
	m_Transform = _gameObject->GetTransform();

	m_bOrthogonal = false;
	m_b6DoF = false;

	m_v3Up = glm::vec3(0, 1.0f, 0);
	m_v3Forward = glm::vec3(-1.0f, 0, 0);

	m_fFOVy = 45.0f;

	m_fAspectRatio = GameWindow::GetCurrentWindow()->GetWidth() / GameWindow::GetCurrentWindow()->GetHeight();
	m_fMinPlane = 0.001f;
	m_fMaxPlane = 100.0f;
	m_fHeight = GameWindow::GetCurrentWindow()->GetHeight();

	CalculateDirectionVectors();
	CalculateView();
	CalculateProjection();
}

Camera::~Camera(){}

void Camera::CalculateView()
{
	CalculateDirectionVectors();

	glm::vec3 v3Position = m_Transform->GetPosition();

	m_m4View = glm::lookAt(v3Position, v3Position + m_v3Forward, m_v3Up);
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

// Calculates the Up, Forward, and Right vectors from the orientation.
void Camera::CalculateDirectionVectors()
{
	m_v3Right = glm::cross(m_v3Forward, m_v3Up);

	glm::vec3 v3Orientation = m_Transform->GetRotation();

	// Compute quaternion for pitch based on the camera pitch angle
	glm::quat qPitch = glm::angleAxis(v3Orientation.x, m_v3Right);
	// Compute quaternion for Yaw based on the camera pitch angle
	glm::quat qYaw = glm::angleAxis(v3Orientation.y, m_v3Up);
	//Compute quaternion for Roll based on the camera pitch angle
	glm::quat qRoll = glm::angleAxis(v3Orientation.z, m_v3Forward);

	//Add the quaternions
	glm::quat qTemp = qPitch * qYaw;

	m_v3Forward = qTemp *  m_v3Forward;


	// Changes the Up and Right vector if Six Degrees of Freedom is set.
	if (m_b6DoF)
	{
		qTemp = glm::cross(qRoll, qPitch);
		m_v3Up = qTemp * m_v3Up;

		qTemp = glm::cross(qYaw, qRoll);
		m_v3Right = qTemp * m_v3Right;
	}

	m_v3Forward = glm::normalize(m_v3Forward);
	m_v3Up = glm::normalize(m_v3Up);
	m_v3Right = glm::normalize(m_v3Right);
}

glm::mat4 Camera::GetView()
{
	return m_m4View;
}
glm::mat4  Camera::GetProjection()
{
	return m_m4Projection;
}

void Camera::LookAtDirection(glm::vec3 a_v3Direction)
{
	// Makes sure the new direction vector actually points somewhere.
	if (a_v3Direction.length() != 0)
	{
		m_v3Forward = a_v3Direction;

		CalculateView();
	}
}
void Camera::LookAtPosition(glm::vec3 a_v3Target)
{
	glm::vec3 v3Position = m_Transform->GetPosition();

	// Makes sure the new target location is not the current location
	if (a_v3Target != v3Position)
	{
		m_v3Forward = a_v3Target - v3Position;

		CalculateView();
	}
}

glm::vec3 Camera::GetPosition()
{
	return m_Transform->GetPosition();;
}
void Camera::SetPosition(glm::vec3 a_v3Position)
{
	m_Transform->SetPosition(a_v3Position);
	CalculateView();
}

glm::vec3 Camera::GetOrientation()
{
	return m_Transform->GetRotation();
}
void Camera::SetOrientation(glm::vec3 a_v3Orientation)
{
	m_Transform->SetPosition(a_v3Orientation);

	CalculateDirectionVectors();
	CalculateView();
}

glm::vec3 Camera::GetUp()
{
	return m_v3Up;
}
void Camera::SetUp(glm::vec3 a_v3Up)
{
	m_v3Up = a_v3Up;
}

glm::vec3 Camera::GetForward()
{
	return m_v3Forward;
}
void Camera::SetForward(glm::vec3 a_v3Forward)
{
	m_v3Forward = a_v3Forward;
}

// Move Camera
void Camera::MoveForward(float a_fIncrement)
{
	glm::vec3 v3Position = m_Transform->GetPosition();

	v3Position += m_v3Forward * a_fIncrement;

	m_Transform->SetPosition(v3Position);
	CalculateView();
}
void Camera::MoveRight(float a_fIncrement)
{
	glm::vec3 v3Position = m_Transform->GetPosition();

	v3Position += m_v3Right * a_fIncrement;

	m_Transform->SetPosition(v3Position);
	CalculateView();
}
void Camera::MoveUp(float a_fIncrement)
{
	glm::vec3 v3Position = m_Transform->GetPosition();

	v3Position += m_v3Up * a_fIncrement;

	m_Transform->SetPosition(v3Position);
	CalculateView();
}

// Rotate Camera
void Camera::ChangePitch(float a_fIncrement)
{
	glm::vec3 v3Orientation = m_Transform->GetRotation();

	v3Orientation.x = a_fIncrement;

	m_Transform->SetRotation(v3Orientation);

	CalculateDirectionVectors();
	CalculateView();
}
void Camera::ChangeYaw(float a_fIncrement)
{
	glm::vec3 v3Orientation = m_Transform->GetRotation();
	
	v3Orientation.y = a_fIncrement;

	m_Transform->SetRotation(v3Orientation);

	CalculateDirectionVectors();
	CalculateView();
}
void Camera::ChangeRoll(float a_fIncrement)
{
	glm::vec3 v3Orientation = m_Transform->GetRotation();
	
	v3Orientation.z = a_fIncrement;

	m_Transform->SetRotation(v3Orientation);

	CalculateDirectionVectors();
	CalculateView();
}
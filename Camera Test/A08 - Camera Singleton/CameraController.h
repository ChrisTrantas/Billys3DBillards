#pragma once
#include "Camera.h"

class CameraController
{
public:
	Camera* m_pCamera = nullptr;

	vector3 m_v3Target = vector3();

	float m_fDistance = 20.0f;
	float m_fHeight = 5.0f;

	float m_fHeightDamping = 4.0f;
	float m_fPositionDamping = 8.0f;
	float m_fRotationDamping = 0.1f;

	CameraController()
	{

	}

	CameraController(Camera* a_pCamera)
	{
		m_pCamera = a_pCamera;
	}
	~SmoothFollow()
	{

	}

	void SetTarget(vector3 a_v3Target)
	{
		m_v3Target = a_v3Target;
	}

	void Update(float fDeltaTime)
	{
		// Calculate the position 

		// Gets the camera's current position
		vector3 v3CurrentPosition = m_pCamera->GetPosition();

		// Finds the camera's desired position
		vector3 v3DesiredPosition = v3CurrentPosition - m_v3Target;

		if (glm::length(v3DesiredPosition) == 0)
		{
			v3DesiredPosition = -m_pCamera->GetForward() * m_fDistance;
		}
		else
		{
			v3DesiredPosition = glm::normalize(v3DesiredPosition) * m_fDistance;
		}

		v3DesiredPosition.y = m_fHeight;

		v3DesiredPosition += m_v3Target;

		// Lerps towards the desired position
		vector3 v3NewPosition = glm::lerp(v3CurrentPosition, v3DesiredPosition, m_fPositionDamping * fDeltaTime);

		// Sets the camera's position
		m_pCamera->SetPosition(v3NewPosition);

		// Tell camera where to look

		vector3 v3CurrentForward = m_pCamera->GetForward();
		vector3 v3DesiredForward = m_v3Target - v3CurrentPosition;
		vector3 v3NewForward = glm::lerp(v3CurrentForward, v3DesiredForward, m_fRotationDamping * fDeltaTime);

		m_pCamera->LookAtDirection(v3NewForward);
	}
};


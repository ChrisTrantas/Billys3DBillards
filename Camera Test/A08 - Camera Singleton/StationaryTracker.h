#pragma once
#include "Camera.h"

class StationaryTracker
{
public:
	Camera* m_pCamera = nullptr;

	vector3 m_v3Target = vector3();

	float m_fDistance = 20.0f;
	float m_fHeight = 5.0f;

	float m_fDamping = 0.5f;
	StationaryTracker()
	{

	}

	StationaryTracker(Camera* a_pCamera)
	{
		m_pCamera = a_pCamera;
	}
	~StationaryTracker()
	{

	}

	void SetTarget(vector3 a_v3Target)
	{
		m_v3Target = a_v3Target;
	}

	void Update(float fDeltaTime)
	{
		// Tell the camera where to look
		vector3 v3CurrentForward = m_pCamera->GetForward();
		vector3 v3DesiredForward = m_v3Target - m_pCamera->GetPosition();
		vector3 v3NewForward = glm::lerp(v3CurrentForward, v3DesiredForward, m_fDamping * fDeltaTime);

		m_pCamera->LookAtDirection(v3NewForward);
	}
};


#include "SmoothFollow.h"


SmoothFollow::SmoothFollow(GameObject* gameObject)
	: Component(gameObject)
{
	m_ObjectTransform = gameObject->GetTransform();
	m_TargetTransform = nullptr;
	m_pCamera = gameObject->GetComponent<Camera>();

	m_fDistance = 20.0f;
	m_fHeight = 25.0f;

	m_fPositionDamping = 8.0f;
	m_fRotationDamping = 8.0f;
}


SmoothFollow::~SmoothFollow()
{
}

void SmoothFollow::SetTarget(Transform* a_TargetTransform)
{
	m_TargetTransform = a_TargetTransform;
}

void SmoothFollow::Update()
{
	if (m_pCamera != nullptr && m_TargetTransform != nullptr)
	{
		float fDeltaTime = Time::GetElapsedTime();

		// Calculate the position 
		// Gets the camera's current position
		glm::vec3 v3CurrentPosition = m_ObjectTransform->GetPosition();

		glm::vec3 v3TargetPosition = m_TargetTransform->GetPosition();

		// Finds the camera's desired position
		glm::vec3 v3DesiredPosition = v3CurrentPosition - v3TargetPosition;

		if (glm::length(v3DesiredPosition) == 0)
		{
			v3DesiredPosition = -m_pCamera->GetForward() * m_fDistance;
		}
		else
		{
			v3DesiredPosition = glm::normalize(v3DesiredPosition) * m_fDistance;
		}

		v3DesiredPosition.y = m_fHeight;

		v3DesiredPosition += v3TargetPosition;

		// Lerps towards the desired position
		glm::vec3 v3NewPosition = glm::mix(v3CurrentPosition, v3DesiredPosition, m_fPositionDamping * fDeltaTime);

		// Sets the camera's position
		m_ObjectTransform->SetPosition(v3NewPosition);

		// Tell camera where to look
		glm::vec3 v3CurrentForward = m_pCamera->GetForward();
		glm::vec3 v3DesiredForward = v3TargetPosition - v3CurrentPosition;
		glm::vec3 v3NewForward = glm::mix(v3CurrentForward, v3DesiredForward, m_fRotationDamping * fDeltaTime);	// Lerps the forward direction to the desired forward

		// Sets the camera to look at that direction
		m_pCamera->LookAtDirection(v3NewForward);
	}
}
#include "Tracker.h"


Tracker::Tracker(GameObject* gameObject)
	: Component(gameObject)
{
	m_pCamera = _gameObject->GetComponent<Camera>();
	m_TargetTransform = nullptr;
	m_ObjectTransform = _gameObject->GetTransform();

	m_fDamping = 0.5f;
}


Tracker::~Tracker()
{
}

void Tracker::SetTarget(Transform* transform)
{
	m_TargetTransform = transform;
}

void Tracker::Update()
{
	float fDeltaTime = Time::GetElapsedTime();

	if (m_TargetTransform != nullptr && m_pCamera != nullptr)
	{
		// Tell the camera where to look
		glm::vec3 v3CurrentForward = m_pCamera->GetForward();
		glm::vec3 v3DesiredForward = m_TargetTransform->GetPosition() - m_ObjectTransform->GetPosition();
		glm::vec3 v3NewForward = glm::mix(v3CurrentForward, v3DesiredForward, m_fDamping * fDeltaTime);

		m_pCamera->LookAtDirection(v3NewForward);
	}
}

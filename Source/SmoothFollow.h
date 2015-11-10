#pragma once
#include "Component.hpp"
#include "Camera.h"
#include "Time.hpp"

class SmoothFollow :
	public Component
{
private:
	Camera* m_pCamera;

	Transform* m_ObjectTransform;
	Transform* m_TargetTransform;

	float m_fDistance;
	float m_fHeight;

	float m_fPositionDamping;
	float m_fRotationDamping;

public:
	SmoothFollow(GameObject* gameObject);
	~SmoothFollow();

	void SetTarget(Transform* a_TargetTransform);
	void Update() override;
};


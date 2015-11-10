#pragma once
#include "Component.hpp"
#include "Camera.h"
#include "Time.hpp"

class Tracker :
	public Component
{
private:
	Camera* m_pCamera;

	Transform* m_ObjectTransform;
	Transform* m_TargetTransform;

	float m_fDamping;
public:
	Tracker(GameObject* gameObject);
	~Tracker();
	void Update() override;
};


#pragma once
#include "Component.hpp"
#include "Camera.h"
#include "Time.hpp"

class FPSController :
	public Component
{
private:
	Camera* m_pCamera;

	glm::vec2 m_v2MousePosition;	// Stores current mouse position

	float m_fSpeed;
	float m_fSensitivity;

public:
	FPSController(GameObject* gameObject);
	~FPSController();

	void Update() override;
};


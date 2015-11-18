#pragma once
#include "Component.hpp"
#include "Camera.h"
#include "Time.hpp"
#include <GLFW\glfw3.h>;

class FPSController :
	public Component
{
private:
	Camera* m_pCamera;

	glm::vec2 m_v2MousePosition;	// Stores current mouse position

	GLFWwindow* window;

	float m_fSpeed;
	float m_fSensitivity;

	void HandleCameraMove();
	void HandleCameraRotate();

public:
	FPSController(GameObject* gameObject);
	~FPSController();

	void Update() override;
};


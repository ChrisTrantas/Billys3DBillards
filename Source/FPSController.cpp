#include "FPSController.h"
#include <GLFW\glfw3.h>;
#include <iostream>


FPSController::FPSController(GameObject* gameObject)
	: Component(gameObject)
{
	m_pCamera = _gameObject->GetComponent<Camera>();

	m_fSpeed = 10.0f;
	float m_fSensitivity = 0.0001f;
}


FPSController::~FPSController()
{
}

void FPSController::Update()
{
	float fDeltaTime = Time::GetElapsedTime();

	// Movement Controls

	
	GLFWwindow* window = glfwGetCurrentContext();

	
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
		m_pCamera->MoveForward(m_fSpeed * fDeltaTime);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
		m_pCamera->MoveForward(-m_fSpeed * fDeltaTime);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
		m_pCamera->MoveRight(-m_fSpeed * fDeltaTime);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
		m_pCamera->MoveRight(m_fSpeed * fDeltaTime);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q))
		m_pCamera->MoveUp(-m_fSpeed * fDeltaTime);
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E))
		m_pCamera->MoveUp(m_fSpeed * fDeltaTime);




	// Mouse Aiming
	double x, y;

	glfwGetCursorPos(window, &x, &y);



	glm::vec2 v2NewMousePosition = glm::vec2((float)x, (float)y);
	glm::vec2 v2MouseMovement = v2NewMousePosition - m_v2MousePosition;

	if (v2MouseMovement.x != 0)
	{
		float increment = -v2MouseMovement.x * fDeltaTime * m_fSensitivity;
		m_pCamera->ChangeYaw(increment);
	}

	if (v2MouseMovement.y != 0);
		//m_pCamera->ChangePitch(-v2MouseMovement.y * glm::pi<float>() / 720.0f * fDeltaTime * m_fSensitivity);



	m_v2MousePosition = v2NewMousePosition;
}
#include "FPSController.h"

FPSController::FPSController(GameObject* gameObject)
	: Component(gameObject)
{
	m_pCamera = _gameObject->GetComponent<Camera>();

	m_fSpeed = 10.0f;
	m_fSensitivity = 1.0f / 10.0f;

	window = glfwGetCurrentContext();
}


FPSController::~FPSController()
{
}

void FPSController::Update()
{
	float fDeltaTime = Time::GetElapsedTime();

	// Movement Controls
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

	glm::vec2 v2NewMousePosition = glm::vec2(x, y);
	glm::vec2 v2MouseMovement = v2NewMousePosition - m_v2MousePosition;

	m_pCamera->ChangeYaw(-v2MouseMovement.x * m_fSensitivity * fDeltaTime);
	m_pCamera->ChangePitch(-v2MouseMovement.y * m_fSensitivity * fDeltaTime);

	m_v2MousePosition = v2NewMousePosition;
}
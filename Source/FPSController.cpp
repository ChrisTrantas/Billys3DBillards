#include "FPSController.h"

FPSController::FPSController(GameObject* gameObject)
    : Component(gameObject)
{
    m_pCamera = _gameObject->GetComponent<Camera>();

    m_fSpeed = 10.0f;
    m_fSensitivity = 1.0f / 10.0f;

}


FPSController::~FPSController()
{
}


void FPSController::Update()
{
	float fDeltaTime = Time::GetElapsedTime();

	// Movement Controls
	if (Input::IsKeyDown(Key::W))
	{
		m_pCamera->MoveForward(m_fSpeed * fDeltaTime);
	}
	if (Input::IsKeyDown(Key::S))
	{
		m_pCamera->MoveForward(-m_fSpeed * fDeltaTime);
	}
	if (Input::IsKeyDown(Key::A))
	{
		m_pCamera->MoveRight(-m_fSpeed * fDeltaTime);
	}
	if (Input::IsKeyDown(Key::D))
	{
		m_pCamera->MoveRight(m_fSpeed * fDeltaTime);
	}
	if (Input::IsKeyDown(Key::Q))
	{
		m_pCamera->MoveUp(-m_fSpeed * fDeltaTime);
	}
	if (Input::IsKeyDown(Key::E))
	{
		m_pCamera->MoveUp(m_fSpeed * fDeltaTime);
	}

	// Mouse Aiming
	glm::vec2 v2MouseMovement = Input::GetDeltaMousePosition();

	m_pCamera->ChangeYaw(-v2MouseMovement.x * m_fSensitivity * fDeltaTime);
	m_pCamera->ChangePitch(-v2MouseMovement.y * m_fSensitivity * fDeltaTime);
}
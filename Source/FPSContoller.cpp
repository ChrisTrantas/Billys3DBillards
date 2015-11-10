#include "FPSContoller.h"


FPSContoller::FPSContoller(GameObject* gameObject)
	: Component(gameObject)
{
	m_pCamera = _gameObject->GetComponent<Camera>();

	m_fSpeed = 10.0f;
	float m_fSensitivity = 10.0f;
}


FPSContoller::~FPSContoller()
{
}

void FPSContoller::Update()
{
	float fDeltaTime = Time::GetElapsedTime();

	// Movement Controls
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCamera->MoveForward(m_fSpeed * fDeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCamera->MoveForward(-m_fSpeed * fDeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCamera->MoveRight(-m_fSpeed * fDeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCamera->MoveRight(m_fSpeed * fDeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCamera->MoveUp(-m_fSpeed * fDeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCamera->MoveUp(m_fSpeed * fDeltaTime);
	*/




	// Mouse Aiming
	/*
	sf::Vector2i v2NewMousePosition = sf::Mouse::getPosition();
	sf::Vector2i v2MouseMovement = v2NewMousePosition - m_v2MousePosition;

	if (v2MouseMovement.x != 0)
		m_pCamera->ChangeYaw(-v2MouseMovement.x * fDeltaTime * m_fSensitivity);

	if (v2MouseMovement.y != 0)
		m_pCamera->ChangePitch(-v2MouseMovement.y * fDeltaTime * m_fSensitivity);

	m_v2MousePosition = v2NewMousePosition;
	*/
}
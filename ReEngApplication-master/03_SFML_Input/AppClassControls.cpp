#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;
	//m_m4SelectedObject = m_pMeshMngr->GetModelMatrix(m_sSelectedObject);

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);
	m_pCameraMngr->CalculateView();
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape,NULL,PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
	ON_KEY_PRESS_RELEASE(F5,NULL,m_pMeshMngr->m_pModelMngr->GenerateOctree())
	static bool bVisible = false;
	ON_KEY_PRESS_RELEASE(F6, bVisible = !bVisible, m_pMeshMngr->m_pModelMngr->SetVisibleOctree(bVisible))
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
	}
}
void AppClass::ProcessJoystick(void)
{
	float fDirection = 1.0f;
	int nPad = 0;
	sf::Joystick::update();
	if(sf::Joystick::isConnected(nPad))
	{
#pragma region Camera Position / Orientation
		if(sf::Joystick::isButtonPressed(nPad, 4) && sf::Joystick::isButtonPressed(nPad, 5))
			exit(0);

		float fAngleX = 0.0f;
		float fAngleY = 0.0f;
		float fSpeed = 0.0001f;

		if(sf::Joystick::isButtonPressed(nPad, 8) && sf::Joystick::isButtonPressed(nPad, 9))	
		{
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			m_pCameraMngr->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
		}

		float fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Y);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta *= fSpeed;
			m_pCameraMngr->MoveForward(-fDelta);
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::X);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta *= fSpeed;
			m_pCameraMngr->MoveSideways(fDelta);
		}

		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Z);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta *= fSpeed;
			m_pCameraMngr->MoveVertical(fDelta);
		}

		fDelta = -sf::Joystick::getAxisPosition(nPad, sf::Joystick::R);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleX -= fDelta * fSpeed;
			fAngleX *= -20.0f;
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::U);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleY -= fDelta * fSpeed;
			fAngleY *= 20.0f;
		}
		m_pCameraMngr->ChangeYaw(fAngleY);
		m_pCameraMngr->ChangePitch(fAngleX);
		m_pCameraMngr->CalculateView();
#pragma endregion
	}
}
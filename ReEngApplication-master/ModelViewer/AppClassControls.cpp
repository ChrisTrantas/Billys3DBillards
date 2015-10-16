#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

	int nMesh = m_pMeshMngr->IdentifyInstance(m_sSelectedObject);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_qArcBall = m_qOrientation = quaternion();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(glm::radians(1.0f), 0.0f, 0.0f));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(glm::radians(-1.0f), 0.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, glm::radians(1.0f), 0.0f));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, glm::radians(-1.0f), 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (!bModifier)
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, 0.0f, glm::radians(1.0f)));
		else
			m_qOrientation = m_qOrientation * quaternion(vector3(0.0f, 0.0f, glm::radians(-1.0f)));
	}

	//Model States
#pragma region Model States
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 4);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 6);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 7);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 8);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		m_pMeshMngr->m_pModelMngr->SetNextState(m_sSelectedObject, 9);
	}
#pragma endregion

#pragma region Model Loading
	//Model Loading
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
		FileReaderClass pFile;
		String sFileName = pFile.RetriveFileNameFromExplorer(L"OBJ Files (*.obj)\0*.obj\0ATO Files (*.ato)\0*.ato\0BTO Files (*.bto)\0*.bto\0", L"obj");
		if (sFileName != "")
		{
			bool bThreaded = m_pSystem->GetThreaded();
			m_pSystem->SetThreaded(false);

			m_pMeshMngr->m_pModelMngr->DeleteInstance();
			m_sSelectedObject = pFile.GetFileName(sFileName);
			m_pMeshMngr->LoadModel(sFileName, m_sSelectedObject, true);

			bool bTest = m_pMeshMngr->IsInstanceCreated(m_sSelectedObject);
			if (bTest)
			{
				BoundingObjectClass* pBO = m_pMeshMngr->GetBoundingObject(m_sSelectedObject);
				vector3 v3Centroid = pBO->GetCentroidGlobal();
				vector3 v3HalfWidth = pBO->GetHalfWidth();
				float fSize = v3HalfWidth.x;
				if (fSize < v3HalfWidth.y)
					fSize = v3HalfWidth.y;
				m_pCameraMngr->SetPositionAndView(v3Centroid + REAXISZ * 2.5f * fSize, v3Centroid);
			}

			m_pSystem->SetThreaded(bThreaded);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
	{
		if (m_sSelectedObject != "")
		{
			bool bThreaded = m_pSystem->GetThreaded();
			m_pSystem->SetThreaded(false);
			FileReaderClass pFile;
			String sFileName = pFile.IndicateFileNameOnExplorer(L"BTO Files (*.bto)\0*.bto\0ATO Files (*.ato)\0*.ato\0All Files (*.*)\0*.*\0", L"bto");
			if (sFileName != "")
			{
				m_pMeshMngr->SaveModel(sFileName, m_sSelectedObject, true);
			}

			m_pSystem->SetThreaded(bThreaded);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		m_pMeshMngr->m_pModelMngr->DeleteInstance(m_sSelectedObject);
		m_sSelectedObject = "";
	}
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
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
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
}

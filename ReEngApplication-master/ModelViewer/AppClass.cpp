#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Model Viewer"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}
void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPosition(REAXISZ * 15.0f);

	m_sSelectedObject = "";
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC)
		CameraRotation();

	if (m_bArcBall)
		m_qArcBall = ArcBall();

	if (m_sSelectedObject != "")
	{
		m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qOrientation * m_qArcBall), m_sSelectedObject);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList(m_sSelectedObject);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(); //renders the XY grid with a 100% scale

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}

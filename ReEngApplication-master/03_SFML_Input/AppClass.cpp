#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("SFML CONTROLS (Esc to terminate)");
}

void AppClass::InitVariables(void)
{
	//Load a model into memory
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();
	//Update the information on the Mesh manager I will not check for collision detection so the argument is false
	m_pMeshMngr->Update(false);

	//Is the arcball active?
	if (m_bArcBall == true)
		m_qArcBall = ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Modify model's ModelToWorld matrix
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), "Steve");

	//Add a model to the render list
	m_pMeshMngr->AddInstanceToRenderList("Steve");

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//print info into the console
	printf("FPS: %d            \r", m_pSystem->GetFPS());//print the Frames per Second
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(10.0f, REAXIS::XY | REAXIS::XZ | REAXIS::YZ); //renders the grid in all views with a 10x scale

	m_pMeshMngr->Render(); //Renders everything set up in the render queue

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
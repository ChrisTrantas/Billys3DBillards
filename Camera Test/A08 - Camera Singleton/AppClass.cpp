#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Michael Cooper - Camera Test"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	selectedCamera = 1;

	myCamera1 = Camera();
	myCamera1.SetPosition(vector3(10.0f, 10.0f, 10.0f));

	myCamera2 = Camera();
	myCamera2.SetPosition(vector3(10.0f, 0, 0));

	myCamera3 = Camera();
	myCamera3.SetPosition(vector3(0, 0, 10.0f));


	mySmoothFollow = SmoothFollow(&myCamera1);
	myFPSCamera = FPSCamera(&myCamera2);
	myStationaryTracker = StationaryTracker(&myCamera3);

	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");

	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(0.0f, 0.0f, -3.0f) * glm::scale(vector3(5.0f)));
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(5.0f, 0.0f, -3.0f) * glm::scale(vector3(5.0f)));
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(-5.0f, 0.0f, -3.0f) * glm::scale(vector3(5.0f)));
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper", false, glm::translate(0.0f, 10.0f, -3.0f) * glm::scale(vector3(5.0f)));
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);


	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static float fRunTime = 0.0f;
	fRunTime += fCallTime;

	static vector3 v3StevePosition = vector3(0);

	v3StevePosition = vector3(10 * cos(fRunTime), 10 * sin(fRunTime), 0);
	m_pMeshMngr->SetModelMatrix(glm::translate(v3StevePosition), "Steve");
	

	switch (selectedCamera)
	{
	case 1:
		mySmoothFollow.SetTarget(v3StevePosition);
		mySmoothFollow.Update(fCallTime);

		m_pCamera->SetView(myCamera1.GetView());
		m_pCamera->SetProjection(myCamera1.GetProjection());
		break;
	case 2:
		myFPSCamera.Update(fCallTime);

		m_pCamera->SetView(myCamera2.GetView());
		m_pCamera->SetProjection(myCamera2.GetProjection());
		break;
	case 3:
		myStationaryTracker.SetTarget(v3StevePosition);
		myStationaryTracker.Update(fCallTime);

		m_pCamera->SetView(myCamera3.GetView());
		m_pCamera->SetProjection(myCamera3.GetProjection());
		break;
	}


	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
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

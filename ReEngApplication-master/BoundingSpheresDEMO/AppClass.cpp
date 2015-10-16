#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}
void AppClass::InitVariables(void)
{
	m_pMesh = new MeshClass();

	std::vector<vector3> lList;
	lList.push_back(vector3(0.0f, 0.0f, 0.0f));
	lList.push_back(vector3(5.0f, 0.0f, 0.0f));
	lList.push_back(vector3(2.5f, 2.5f, -2.5f));

	lList.push_back(vector3(5.0f, 0.0f, 0.0f));
	lList.push_back(vector3(2.5f, 0.0f, -5.0f));
	lList.push_back(vector3(2.5f, 2.5f, -2.5f));

	lList.push_back(vector3(2.5f, 0.0f, -5.0f));
	lList.push_back(vector3(0.0f, 0.0f, 0.0f));
	lList.push_back(vector3(2.5f, 2.5f, -2.5f));

	lList.push_back(vector3(0.0f, 0.0f, 0.0f));
	lList.push_back(vector3(2.5f, 0.0f, -5.0f));
	lList.push_back(vector3(5.0f, 0.0f, 0.0f));
	
	m_vMin = m_vMax = lList[0];
	
	//for making our shape
	for (uint i = 0; i < lList.size(); i++)
	{
		m_pMesh->AddVertexPosition(lList[i]);
	}

	for (uint i = 1; i < lList.size(); i++)
	{
		if (m_vMax.x < lList[i].x)
			m_vMax.x = lList[i].x;
		else if (m_vMin.x > lList[i].x)
			m_vMin.x = lList[i].x;

		if (m_vMax.y < lList[i].y)
			m_vMax.y = lList[i].y;
		else if (m_vMin.y > lList[i].y)
			m_vMin.y = lList[i].y;

		if (m_vMax.z < lList[i].z)
			m_vMax.z = lList[i].z;
		else if (m_vMin.z > lList[i].z)
			m_vMin.z = lList[i].z;
	}

	m_vCenter = (m_vMax + m_vMin) / 2.0f;

	//fRadius = glm::distance(vCenter, vMax);
	m_fRadius = 0.0f;
	float fDistance;
	for (uint i = 0; i < lList.size(); i++)
	{
		fDistance = glm::distance(m_vCenter, lList[i]);
		if (m_fRadius < fDistance)
			m_fRadius = fDistance;
	}

	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	if (m_bArcBall == true)
		m_qArcball = ArcBall();

	m_pMeshMngr->AddSphereToQueue(glm::scale(glm::translate(glm::mat4_cast(m_qArcball), m_vCenter), vector3(m_fRadius * 2.0f)), REWHITE, WIRE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(); //renders the XY grid with a 100% scale

	m_pMeshMngr->Render(); //renders the render list

	m_pMesh->RenderSolid(glm::mat4_cast(m_qArcball), vector3(1.0f, 1.0f, 0.0f));
	m_pMesh->RenderWire(glm::mat4_cast(m_qArcball), vector3(0.0f, 0.0f, 0.0f));

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}

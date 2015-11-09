#include "CameraManagerSingleton.h"

CameraManagerSingleton* CameraManagerSingleton::instance;

#pragma region Base Singleton Methods
CameraManagerSingleton::CameraManagerSingleton()
{

	 m_vEyePosition = vector3(0, 1, 0);	
	 m_vUp = vector3(0, 1, 0);			
	 m_vForward = vector3(0 ,0 ,-1);
	 m_vRight = vector3(1, 0, 0);
	 m_vTarget = vector3(0);		

	 m_qOrientation = quaternion(vector3(0,0,0));

	 GenerateViewMatrix();
}


CameraManagerSingleton::~CameraManagerSingleton()
{
}


CameraManagerSingleton* CameraManagerSingleton::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CameraManagerSingleton();
	}

	return instance;
}


void CameraManagerSingleton::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
#pragma endregion

#pragma region Getters
matrix4 CameraManagerSingleton::GetView()
{
	return m_m4View;
}

matrix4 CameraManagerSingleton::GetProjection(bool bOrthographic)
{
	return bOrthographic ? glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 30.0f) : glm::perspective(45.0f, 1000.0f / 720.0f, 0.01f, 1000.0f);
}

quaternion CameraManagerSingleton::GetOrientation()
{
	return m_qOrientation;
}

vector3 CameraManagerSingleton::GetUpVector()
{
	return m_vUp;
}
#pragma endregion


void CameraManagerSingleton::GenerateViewMatrix()
{
	// If the m_vForward and -m_vUp vectors do not align, generate new view matrix
	if (m_vForward != m_vUp && m_vForward != -m_vUp)
	{
		m_m4View = glm::lookAt(m_vEyePosition, m_vEyePosition + m_vForward, m_vUp);
	}
}

void CameraManagerSingleton::SetPosition(vector3 vEyePosition)
{
	m_vEyePosition = vEyePosition;


	m_vForward = glm::normalize(m_vTarget - m_vEyePosition);
	m_vRight = glm::cross(m_vForward, m_vUp);

	// Generates new view matrix
	GenerateViewMatrix();

	// Sets new value for orientation quaternion based on the current view matrix
	m_qOrientation = quaternion(glm::transpose(m_m4View));
}

void CameraManagerSingleton::SetTarget(vector3 vTarget)
{
	m_vTarget = vTarget;

	m_vForward = glm::normalize(m_vTarget - m_vEyePosition);
	m_vRight = glm::cross(m_vForward, m_vUp);

	// Generates new view matrix
	GenerateViewMatrix();

	// Sets new value for orientation quaternion based on the current view matrix
	m_qOrientation = quaternion(glm::transpose(m_m4View));
}

void CameraManagerSingleton::SetUp(vector3 vUp)
{
	m_vUp = glm::normalize(vUp);
	m_vRight = glm::cross(m_vForward, m_vUp);

	// Generates new view matrix
	GenerateViewMatrix();

	// Sets new value for orientation quaternion based on the current view matrix
	m_qOrientation = quaternion(glm::transpose(m_m4View));
}


#pragma region Movement
void CameraManagerSingleton::MoveForward(float fIncrement)
{
	m_vEyePosition += m_vForward * fIncrement;
	m_vTarget += m_vForward * fIncrement;

	GenerateViewMatrix();
}

void CameraManagerSingleton::MoveVertical(float fIncrement)
{
	m_vEyePosition += m_vUp * fIncrement;
	m_vTarget += m_vUp * fIncrement;
	
	GenerateViewMatrix();
}

void CameraManagerSingleton::MoveSideways(float fIncrement)
{
	m_vEyePosition += m_vRight * fIncrement;
	m_vTarget += m_vRight * fIncrement;

	GenerateViewMatrix();
}
#pragma endregion

#pragma region Change Orientation
void CameraManagerSingleton::ChangePitch(float fIncrement)
{
	quaternion qTemp = glm::angleAxis(fIncrement, m_vRight);
	
	m_qOrientation = qTemp * m_qOrientation;
	 

	m_vForward = m_qOrientation * vector3(0,0,-1);
	//m_vRight = m_qOrientation * vector3(1, 0, 0);
	m_vUp = m_qOrientation * vector3(0, 1, 0);

	GenerateViewMatrix();
}

void CameraManagerSingleton::ChangeYaw(float fIncrement)
{
	quaternion qTemp = glm::angleAxis(fIncrement, m_vUp);

	m_qOrientation = qTemp * m_qOrientation;

	m_vForward = m_qOrientation * vector3(0, 0, -1);
	m_vRight = m_qOrientation * vector3(1, 0, 0);
	//m_vUp = m_qOrientation * vector3(0, 1, 0);

	GenerateViewMatrix();
}

void CameraManagerSingleton::ChangeRoll(float fIncrement)
{
	quaternion qTemp = glm::angleAxis(fIncrement, m_vForward);

	m_qOrientation = qTemp * m_qOrientation;

	//m_vForward = m_qOrientation * vector3(0, 0, -1);
	m_vRight = m_qOrientation * vector3(1, 0, 0);
	m_vUp = m_qOrientation * vector3(0, 1, 0);

	GenerateViewMatrix();
}
#pragma endregion
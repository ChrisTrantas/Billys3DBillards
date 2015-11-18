#include "CameraManager.h"
#include <GLFW\glfw3.h>


CameraManager::CameraManager(GameObject* gameObject)
	: Component(gameObject)
{
	cameras = std::vector<Camera*>();
	activeCameraIndex = 0;

	upKeyPrevState = GLFW_RELEASE;
	downKeyPrevState = GLFW_RELEASE;
}

CameraManager::~CameraManager()
{
}

void CameraManager::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
}

Camera* CameraManager::GetActiveCamera()
{
	return cameras[activeCameraIndex];
}

void CameraManager::Update()
{
	GLFWwindow* window = glfwGetCurrentContext();

	int upKeyState = glfwGetKey(window, GLFW_KEY_UP);
	int downKeyState = glfwGetKey(window, GLFW_KEY_DOWN);

	if (upKeyPrevState == GLFW_PRESS && upKeyState == GLFW_RELEASE)
	{
		activeCameraIndex++;
		activeCameraIndex = activeCameraIndex % cameras.size();
	}
	else if (downKeyPrevState == GLFW_PRESS && downKeyState == GLFW_RELEASE)
	{
		activeCameraIndex--;
		activeCameraIndex = activeCameraIndex % cameras.size();
	}
	
	upKeyPrevState = upKeyState;
	downKeyPrevState = downKeyState;
}

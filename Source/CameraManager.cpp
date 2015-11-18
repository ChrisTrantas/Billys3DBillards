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
	
	if (cameras.size() > 1)
	{
		camera->GetGameObject()->SetActive(false);
	}
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
		cameras[activeCameraIndex]->GetGameObject()->SetActive(false);
		activeCameraIndex++;
		activeCameraIndex = activeCameraIndex % cameras.size();
		cameras[activeCameraIndex]->GetGameObject()->SetActive(true);
	}
	else if (downKeyPrevState == GLFW_PRESS && downKeyState == GLFW_RELEASE)
	{
		cameras[activeCameraIndex]->GetGameObject()->SetActive(false);
		activeCameraIndex--;
		activeCameraIndex = activeCameraIndex % cameras.size();
		cameras[activeCameraIndex]->GetGameObject()->SetActive(true);
	}
	
	upKeyPrevState = upKeyState;
	downKeyPrevState = downKeyState;
}

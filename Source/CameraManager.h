#pragma once
#include "Camera.h"

class CameraManager
	: public Component
{
	std::vector<Camera*> cameras;
	int activeCameraIndex;

	int upKeyPrevState;
	int downKeyPrevState;

public:
	CameraManager(GameObject*);
	~CameraManager();

	void AddCamera(Camera* camera);

	Camera* GetActiveCamera();

	void Update();
};


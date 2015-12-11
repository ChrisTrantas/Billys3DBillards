#pragma once
#include "Components.hpp"
#include "MeshLoader.hpp"
#include "Game.hpp"

class Game;

class BilliardGameManager
{
	Game* _game = nullptr;

	GameObject* table = nullptr;
	vector<GameObject*> tableColliders = vector<GameObject*>();
	vector<GameObject*> pocketColliders = vector<GameObject*>();

	GameObject* cueball = nullptr;
	vector<GameObject*> balls = vector<GameObject*>();

	// Cameras
	GameObject* _camTopDown;	// Static camera. Looks upon the table
	GameObject* _camFollower;	// Smooth following camera.
	GameObject* _camTracker;	// Stationary tracking camera.
	GameObject* _camFPS;		// FPS camera
	int _TargetBallIndex;	// The index of the currently target ball.
	Camera* activeCamera;

	bool _Ready = false;

	int score = 0;

	// Text

public:
	BilliardGameManager();
	BilliardGameManager(Game* _game);
	~BilliardGameManager();

	void CreateTable();
	void PreparePoolBalls(int rows = 5);

	void Update();

	GameObject* GetCueball()
	{
		return cueball;
	}

	GameObject* GetNumberedPoolBalls();

	Camera* GetActiveCamera()
	{
		return activeCamera;
	}

	void PocketCollision(GameObject*);
};


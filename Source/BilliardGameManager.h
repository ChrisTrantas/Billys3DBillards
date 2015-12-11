#pragma once
#include "Components.hpp"
#include "MeshLoader.hpp"
#include "Game.hpp"

class Game;

class BilliardGameManager
{
	Game* _Game = nullptr;

	GameObject* _Table = nullptr;
	vector<GameObject*> _TableColliders = vector<GameObject*>();
	vector<GameObject*> _PocketColliders = vector<GameObject*>();

	GameObject* _Cueball = nullptr;
	vector<GameObject*> _Balls = vector<GameObject*>();	// List of numbered balls. DOES NOT INCLUDE Cueball.

	// Cameras
	GameObject* _camTopDown;	// Static camera. Looks upon the table
	GameObject* _camFollower;	// Smooth following camera.
	GameObject* _camTracker;	// Stationary tracking camera.
	GameObject* _camFPS;		// FPS camera
	int _TargetBallIndex;	// The index of the currently target ball.
	Camera* _ActiveCamera;	// The camera currently being drawn for

	bool _IsTableSettled = false;

	int _Score = 0;

	// Text
	TextRenderer* _TextRenderer;

public:
	BilliardGameManager();
	~BilliardGameManager();

	void CreateTable();	// Creates the table with model and colliders
	void PreparePoolBalls(int rows = 5);	// Places the balls into their starting positions
	void HandlePocketCollision(GameObject*);	// Determines what happens when a ball collides with a pocket collider.

	void Update();

	GameObject* GetCueball();
	vector<GameObject*> GetNumberedPoolBalls();
	Camera* GetActiveCamera();
};


#pragma once
#include "Components.hpp"
#include "MeshLoader.hpp"
#include "Game.hpp"

class Game;

class BilliardGameManager
{
	Game* _game = nullptr;

	GameObject* table = nullptr;
	vector<GameObject* > tableColliders = vector<GameObject* >();

	GameObject* cueball = nullptr;
	vector<GameObject* > balls;


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
};


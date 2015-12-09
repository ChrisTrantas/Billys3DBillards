#include "BilliardGameManager.h"
#include "Time.hpp"
#include "Input.hpp"

#define BALL_SIZE 2.0f


BilliardGameManager::BilliardGameManager()
{
}

BilliardGameManager::BilliardGameManager(Game* game)
{
	_game = game;
}

BilliardGameManager::~BilliardGameManager()
{
}

void BilliardGameManager::CreateTable()
{
	// Create the table
	{
		table = _game->AddGameObject("Table");
		SimpleMaterial* tableMaterial = table->AddComponent<SimpleMaterial>();
		MeshRenderer* tableMeshRenderer = table->AddComponent<MeshRenderer>();

		tableMeshRenderer->SetMesh(MeshLoader::Load("Models\\Pool_Table.fbx"));
		tableMeshRenderer->SetMaterial(tableMaterial);
		tableMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Rocks.jpg"));
	}

	// Create the table colliders
	{
		// The table floor
		GameObject* tableFloor = table->AddChild("TableFloor");
		SimpleMaterial* tableFloorMaterial = tableFloor->AddComponent<SimpleMaterial>();
		MeshRenderer* tableFloorMeshRenderer = tableFloor->AddComponent<MeshRenderer>();
		BoxCollider* tableFloorCollider = tableFloor->AddComponent<BoxCollider>();
		RigidBody* tableFloorRigidbody = tableFloor->AddComponent<RigidBody>();

		tableFloorRigidbody->SetMass(0.0f);

		tableFloorMeshRenderer->SetMesh(MeshLoader::Load("Models\\Cube.obj"));
		tableFloorMeshRenderer->SetMaterial(tableFloorMaterial);

		tableFloor->GetTransform()->SetScale(vec3(100, 1, 50));
		tableFloor->GetTransform()->SetPosition(vec3(0, -1.25, 0));

		tableFloorMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

		tableColliders.push_back(tableFloor);

		// The table walls
		for (int i = 0; i < 6; i++)
		{
			GameObject* tableWall = table->AddChild("TableWall_" + std::to_string(i));
			SimpleMaterial* tableWallMaterial = tableWall->AddComponent<SimpleMaterial>();
			MeshRenderer* tableWallMeshRenderer = tableWall->AddComponent<MeshRenderer>();
			BoxCollider* tableWallCollider = tableWall->AddComponent<BoxCollider>();
			RigidBody* tableWallRigidbody = tableWall->AddComponent<RigidBody>();

			tableWallMeshRenderer->SetMesh(MeshLoader::Load("Models\\Cube.obj"));
			tableWallMeshRenderer->SetMaterial(tableWallMaterial);
			tableWallMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

			tableWallRigidbody->SetMass(0.0f);
			tableWallCollider->SetSize(glm::vec3(1));

			switch (i)
			{
			case 0:
				tableWall->GetTransform()->SetScale(vec3(7, 4, 42));
				tableWall->GetTransform()->SetPosition(vec3(53.5f, 1, 0));
				break;
			case 1:
				tableWall->GetTransform()->SetScale(vec3(7, 4, 42));
				tableWall->GetTransform()->SetPosition(vec3(-53.5f, 1, 0));
				break;
			case 2:
				tableWall->GetTransform()->SetScale(vec3(42, 4, 7));
				tableWall->GetTransform()->SetPosition(vec3(-25.0f, 1, -28.5f));
				break;
			case 3:
				tableWall->GetTransform()->SetScale(vec3(42, 4, 7));
				tableWall->GetTransform()->SetPosition(vec3(25.0f, 1, -28.5f));
				break;
			case 4:
				tableWall->GetTransform()->SetScale(vec3(42, 4, 7));
				tableWall->GetTransform()->SetPosition(vec3(-25.0f, 1, 28.5f));
				break;
			case 5:
				tableWall->GetTransform()->SetScale(vec3(42, 4, 7));
				tableWall->GetTransform()->SetPosition(vec3(25.0f, 1, 28.5f));
				break;
			}
			tableColliders.push_back(tableWall);
		}
	}
}

// Places the pool balls into starting position
void BilliardGameManager::PreparePoolBalls(int rows)
{
	if (cueball == nullptr)
	{
		cueball = _game->AddGameObject("CueBall");
		SimpleMaterial* material = cueball->AddComponent<SimpleMaterial>();
		MeshRenderer* meshRenderer = cueball->AddComponent<MeshRenderer>();
		RigidBody* rigidBody = cueball->AddComponent<RigidBody>();
		SphereCollider* collider = cueball->AddComponent<SphereCollider>();

		collider->SetRadius(BALL_SIZE* 0.5f);

		rigidBody->SetMass(1.0f);

		meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
		meshRenderer->SetMaterial(material);

		material->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));
	}


	cueball->GetTransform()->SetPosition(vec3(0.0f, BALL_SIZE * 0.5f, -11));
	cueball->GetTransform()->SetScale(vec3(BALL_SIZE));
	cueball->GetComponent<RigidBody>()->SetVelocity(vec3(0));


	for (GameObject* ball : balls)
	{
		ball->GetComponent<RigidBody>()->SetVelocity(vec3(0));
	}


	// Create the numbered balls
	for (int row = 1; row <= rows; row++)
	{
		for (int i = 0; i < row; i++)
		{
			GameObject* ball = _game->AddGameObject("Ball_" + std::to_string(row) + '_' + std::to_string(i));
			Transform* transform = ball->GetTransform();
			SimpleMaterial* material = ball->AddComponent<SimpleMaterial>();
			MeshRenderer* meshRenderer = ball->AddComponent<MeshRenderer>();
			RigidBody* rigidBody = ball->AddComponent<RigidBody>();
			SphereCollider* collider = ball->AddComponent<SphereCollider>();

			collider->SetRadius(BALL_SIZE* 0.5f);
			rigidBody->SetMass(1.0f);

			meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
			meshRenderer->SetMaterial(material);

			std::string texName = "Textures\\" + std::to_string((balls.size()) % 15 + 1) + "-Ball.png";
			std::cout << "Loading " << texName << "... ";

			std::shared_ptr<Texture2D> texture = Texture2D::FromFile(texName);
			if (texture)
			{
				material->SetMyTexture(texture);
				std::cout << "Done." << std::endl;
			}
			else
			{
				std::cout << "Failed. ;_;" << std::endl;
			}


			float xPos = (-(row - 1) * 0.7f + i * 1.4f) * BALL_SIZE;
			float zPos = (row * 0.8f) * BALL_SIZE;
			transform->SetPosition(vec3(xPos, BALL_SIZE * 0.5f, zPos));
			transform->SetScale(vec3(BALL_SIZE));

			balls.push_back(ball);
		}
	}
}

void BilliardGameManager::Update()
{
		if (Input::WasKeyPressed(Key::Space))
		{
			cueball->GetComponent<RigidBody>()->AddForce(vec3(0, 0, 4000.0f));
		}
		else if (Input::WasKeyPressed(Key::Enter))
		{
			cueball->GetComponent<RigidBody>()->AddForce(vec3(0, 0, 10000.0f));
		}
		else if (Input::WasKeyPressed(Key::F1))
		{
			PreparePoolBalls(5);
		}
		else if (Input::WasKeyPressed(Key::F2))
		{
			PreparePoolBalls(10);
		}
}
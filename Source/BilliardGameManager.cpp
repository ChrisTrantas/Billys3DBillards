#include "BilliardGameManager.h"
#include "Time.hpp"
#include "Input.hpp"
#include "Physics.hpp"

#define BALL_SIZE 2.0f

#define CUEBALL_NAME "Cueball"

Input* inputController;
vec2 mouseClickPos = inputController->GetMousePosition();

BilliardGameManager::BilliardGameManager()
{
	_game = Game::GetInstance();

	
	// Default Camera
	_camTopDown = _game->AddGameObject("CameraObject");
	Camera* camera = _camTopDown->AddComponent<Camera>();
	camera->SetPosition(vec3(0, 50, 30));
	camera->LookAtPosition(vec3(0, 0, 0));

	// Following Camera
	_camFollower = _game->AddGameObject("CameraObjectSmoothFollow");
	Camera* cameraSmoothFollower = _camFollower->AddComponent<Camera>();
	cameraSmoothFollower->SetPosition(vec3(-4, 4, -4));
	SmoothFollow* smoothFollow = _camFollower->AddComponent<SmoothFollow>();


	// Tracker Camera
	_camTracker = _game->AddGameObject("CameraObjectTracker");
	Camera* cameraTracker = _camTracker->AddComponent<Camera>();
	cameraTracker->SetPosition(vec3(0, 50, 30));
	Tracker* tracker = _camTracker->AddComponent<Tracker>();


	// FPS Camera
	_camFPS = _game->AddGameObject("CameraObjectFPS");
	Camera* cameraFPS = _camFPS->AddComponent<Camera>();
	cameraFPS->SetPosition(vec3(0, 50, 30));
	FPSController* fPSController = _camFPS->AddComponent<FPSController>();
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



	std::function<void(GameObject*)> func = std::bind(&BilliardGameManager::PocketCollision, this, _1);

	for (unsigned int i = 0; i < 6; i++)
	{
		GameObject* pocket = _game->AddGameObject("Pocket_" + std::to_string(i));
		SimpleMaterial* pocketMaterial = pocket->AddComponent<SimpleMaterial>();
		MeshRenderer* pocketMeshRenderer = pocket->AddComponent<MeshRenderer>();
		SphereCollider* pocketCollider = pocket->AddComponent<SphereCollider>();
		RigidBody* pocketRigidbody = pocket->AddComponent<RigidBody>();

		pocketCollider->SetRadius(3.1);
		pocketRigidbody->SetMass(0.0f);
		pocketRigidbody->SetMovable(false);

		pocketMeshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
		pocketMeshRenderer->SetMaterial(pocketMaterial);

		pocket->GetTransform()->SetScale(vec3(8, 4, 8));

		pocketMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

		pocket->GetEventListener()->AddEventListener("OnCollide", func);


		switch (i)
		{
		case 0:
			pocket->GetTransform()->SetPosition(vec3(50, 0, 25));
			break;
		case 1:
			pocket->GetTransform()->SetPosition(vec3(0, 0, 25));
			break;
		case 2:
			pocket->GetTransform()->SetPosition(vec3(-50, 0, 25));
			break;
		case 3:
			pocket->GetTransform()->SetPosition(vec3(50, 0, -25));
			break;
		case 4:
			pocket->GetTransform()->SetPosition(vec3(0, 0, -25));
			break;
		case 5:
			pocket->GetTransform()->SetPosition(vec3(-50, 0, -25));
			break;
		}

		pocketColliders.push_back(pocket);
	}
}

// Places the pool balls into starting position
void BilliardGameManager::PreparePoolBalls(int rows)
{
	score = 0;

	if (cueball == nullptr)
	{
		cueball = _game->AddGameObject(CUEBALL_NAME);
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

	cueball->SetActive(true);
	cueball->GetTransform()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
    cueball->GetTransform()->SetScale( vec3( BALL_SIZE ) );
	RigidBody* cueballRigidBody = cueball->GetComponent<RigidBody>();
	cueballRigidBody->SetVelocity(vec3(0));
	cueballRigidBody->SetAcceleration(vec3(0));




	for (GameObject* ball : balls)
	{
		_game->Destroy(ball);
	}
    balls.clear();

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


			//float xPos = (-(row - 1) * 0.7f + i * 1.4f) * BALL_SIZE;
			//float zPos = (row * 0.8f) * BALL_SIZE;

			float xPos = (row * 0.8f) * BALL_SIZE;
			float zPos = (-(row - 1) * 0.7f + i * 1.4f) * BALL_SIZE;

			transform->SetPosition(vec3(xPos, BALL_SIZE * 0.5f, zPos));
			transform->SetScale(vec3(BALL_SIZE));

			balls.push_back(ball);
		}
	}

	activeCamera = _camTopDown->GetComponent<Camera>();


	_camFollower->GetComponent<SmoothFollow>()->SetTarget(cueball->GetTransform());
	_camFollower->GetTransform()->SetPosition(vec3(0.0f, 50.0f, 10.0f));
	_camTracker->GetComponent<Tracker>()->SetTarget(cueball->GetTransform());
}

void BilliardGameManager::Update()
{
	if (cueball->GetComponent<RigidBody>()->IsAtRest())
	{
		_Ready = true;
		for (auto ball : balls)
		{
			if (!ball->GetComponent<RigidBody>()->IsAtRest())
			{
				_Ready = false;
				break;
			}
		}
	}
	else
	{
		_Ready = false;
	}

	{
		vec3 position = cueball->GetTransform()->GetPosition();
		if (glm::abs(position.x) > 70.0f
			|| glm::abs(position.z) > 35.0f)
		{
			cueball->GetTransform()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
		}
	}

	for (auto i = 0; i < balls.size(); i++)
	{
		vec3 position = balls[i]->GetTransform()->GetPosition();
		if (glm::abs(position.x) > 70.0f
			|| glm::abs(position.z) > 35.0f)
		{
			RigidBody* rigidBody = balls[i]->GetComponent<RigidBody>();
			rigidBody->SetVelocity(vec3(0));
			Physics::UnregisterRigidbody(rigidBody);
		}
	}


	if (_Ready && Input::WasKeyReleased(Key::Space))
	{
		cueball->GetComponent<RigidBody>()->AddForce(vec3(4000.0f, 0, 0));
	}
	else if (_Ready && Input::WasKeyReleased(Key::Enter))
	{
		cueball->GetComponent<RigidBody>()->AddForce(vec3(10000.0f, 0, 0));
	}

	// Reset table
	if (Input::WasKeyPressed(Key::F1))
	{
		PreparePoolBalls(5);
	}
	else if (Input::WasKeyPressed(Key::F2))
	{
		PreparePoolBalls(10);
	}
	else if (Input::WasKeyPressed(Key::F3))
	{
		PreparePoolBalls(15);
	}
	else if (Input::WasKeyPressed(Key::F4))
	{
		PreparePoolBalls(20);
	}
	else if (Input::WasKeyPressed(Key::F5))
	{
		PreparePoolBalls(25);
	}
	else if (Input::WasKeyPressed(Key::F6))
	{
		PreparePoolBalls(30);
	}
	else if (Input::WasKeyPressed(Key::F7))
	{
		PreparePoolBalls(35);
	}



	// Change camera mode
	if (Input::WasKeyPressed(Key::Num1))
	{
		activeCamera = _camTopDown->GetComponent < Camera>();
	}
	else if (Input::WasKeyPressed(Key::Num2))
	{
		activeCamera = _camFollower->GetComponent < Camera>();
	}
	else if (Input::WasKeyPressed(Key::Num3))
	{
		activeCamera = _camTracker->GetComponent < Camera>();
	}
	else if (Input::WasKeyPressed(Key::Num4))
	{
		activeCamera = _camFPS->GetComponent < Camera>();
	}

	if (Input::WasKeyReleased(Key::Up))
	{
		_TargetBallIndex = (_TargetBallIndex + 1 + balls.size()) % balls.size();

		_camFollower->GetComponent<SmoothFollow>()->SetTarget(balls[_TargetBallIndex]->GetTransform());
		_camTracker->GetComponent<Tracker>()->SetTarget(balls[_TargetBallIndex]->GetTransform());
	}
	if (Input::WasKeyReleased(Key::Down))
	{
		_TargetBallIndex = (_TargetBallIndex - 1 + balls.size()) % balls.size();

		_camFollower->GetComponent<SmoothFollow>()->SetTarget(balls[_TargetBallIndex]->GetTransform());
		_camTracker->GetComponent<Tracker>()->SetTarget(balls[_TargetBallIndex]->GetTransform());
	}
	if (Input::WasKeyReleased(Key::Tilde))
	{
		_camFollower->GetComponent<SmoothFollow>()->SetTarget(cueball->GetTransform());
		_camTracker->GetComponent<Tracker>()->SetTarget(cueball->GetTransform());
	}

	// Mouse stuff
	if (Input::WasButtonPressed(MouseButton::Left))
	{
		mouseClickPos = inputController->GetMousePosition();
	}

	if (Input::WasButtonReleased(MouseButton::Left))
	{
		std::cout << "mouseX" << mouseClickPos.x << std::endl;
		std::cout << "mouseY" << mouseClickPos.y << std::endl;
		vec2 mouseReleasePos = inputController->GetMousePosition();
		vec2 mousePosDifference = mouseClickPos - mouseReleasePos;
		cueball->GetComponent<RigidBody>()->AddForce(vec3(mousePosDifference.x, 0, mousePosDifference.y));
	}
}

void BilliardGameManager::PocketCollision(GameObject* gameObject)
{
	string name = gameObject->GetName();
	if (name == CUEBALL_NAME)
	{
		std::cout << "Cueball in pocket." << endl;
		PreparePoolBalls();
	}
	else if (name.substr(0,4) == "Ball" )
	{
		std::cout << "Numbered ball in pocket" << endl;
		score++;
		std::cout << score << endl;
		RigidBody* rigidBody = gameObject->GetComponent<RigidBody>();
		rigidBody->SetVelocity(vec3(0));
		Physics::UnregisterRigidbody(gameObject->GetComponent<RigidBody>());
		gameObject->GetTransform()->SetPosition(vec3(-55 + score * 2, 4, -30));
	}

}


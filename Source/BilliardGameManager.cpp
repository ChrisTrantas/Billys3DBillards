#include "BilliardGameManager.h"
#include "Time.hpp"
#include "Input.hpp"
#include "Physics.hpp"

#define BALL_SIZE 2.0f
#define TABLE_TEXTURE "Textures\\Tabel_Texture.png"
#define MAX_FORCE 10000.0f

Input* inputController;
vec2 mouseClickPos = inputController->GetMousePosition();

BilliardGameManager::BilliardGameManager()
{
	_Game = Game::GetInstance();

	// Add a text renderer
	GameObject* textObject = _Game->AddGameObject("TableTextRenderer");
	TextMaterial* textMaterial = textObject->AddComponent<TextMaterial>();
	_TextRenderer = textObject->AddComponent<TextRenderer>();

	std::shared_ptr<Font> font = std::make_shared<Font>();
	assert(font->LoadFromFile("Fonts\\OpenSans-Regular.ttf"));
	_TextRenderer->SetFont(font);
	_TextRenderer->SetFontSize(16U);
	textMaterial->SetTextColor(vec4(0, 0, 0, 1));

	textObject->GetTransform()->SetPosition(glm::vec3(500, 10, 0));


	// Default Camera
	_camTopDown = _Game->AddGameObject("Top Down Camera");
	Camera* camera = _camTopDown->AddComponent<Camera>();
	camera->SetPosition(vec3(0, 50, 40));
	camera->LookAtPosition(vec3(0, 0, 0));

	// Following Camera
	_camFollower = _Game->AddGameObject("Smooth Following Camera");
	Camera* cameraSmoothFollower = _camFollower->AddComponent<Camera>();
	cameraSmoothFollower->SetPosition(vec3(-4, 4, -4));
	SmoothFollow* smoothFollow = _camFollower->AddComponent<SmoothFollow>();


	// Tracker Camera
	_camTracker = _Game->AddGameObject("Stationary Tracking Camera");
	Camera* cameraTracker = _camTracker->AddComponent<Camera>();
	cameraTracker->SetPosition(vec3(0, 50, 30));
	Tracker* tracker = _camTracker->AddComponent<Tracker>();


	// FPS Camera
	_camFPS = _Game->AddGameObject("FPS Camera");
	Camera* cameraFPS = _camFPS->AddComponent<Camera>();
	cameraFPS->SetPosition(vec3(0, 1, 0));
	cameraFPS->LookAtPosition(vec3(0, 0, -11));
	FPSController* fPSController = _camFPS->AddComponent<FPSController>();
}

BilliardGameManager::~BilliardGameManager()
{
}

void BilliardGameManager::CreateTable()
{
	// Create the table

	_Table = _Game->AddGameObject("Table");
	SimpleMaterial* tableMaterial = _Table->AddComponent<SimpleMaterial>();
	MeshRenderer* tableMeshRenderer = _Table->AddComponent<MeshRenderer>();

	tableMeshRenderer->SetMesh(MeshLoader::Load("Models\\Pool_Table.fbx"));
	tableMeshRenderer->SetMaterial(tableMaterial);
	tableMaterial->SetMyTexture(Texture2D::FromFile(TABLE_TEXTURE));


	// Create the table colliders

	// The table floor
	GameObject* tableFloor = _Table->AddChild("TableFloor");
	BoxCollider* tableFloorCollider = tableFloor->AddComponent<BoxCollider>();
	RigidBody* tableFloorRigidbody = tableFloor->AddComponent<RigidBody>();

	tableFloorRigidbody->SetMass(0.0f);


	tableFloor->GetTransform()->SetScale(vec3(100, 1, 50));
	tableFloor->GetTransform()->SetPosition(vec3(0, -1.25, 0));

	_TableColliders.push_back(tableFloor);

	// The table walls
	for (int i = 0; i < 6; i++)
	{
		GameObject* tableWall = _Table->AddChild("TableWall_" + std::to_string(i));
		BoxCollider* tableWallCollider = tableWall->AddComponent<BoxCollider>();
		RigidBody* tableWallRigidbody = tableWall->AddComponent<RigidBody>();


		tableWallRigidbody->SetMass(0.0f);
		tableWallCollider->SetSize(glm::vec3(1));

		// Place the wall colliders into position
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
		_TableColliders.push_back(tableWall);
	}


	// Pocket Colliders

	// Creates a function pointer to be subscribed to the event listeners of the pocket colliders
	std::function<void(GameObject*)> func = std::bind(&BilliardGameManager::HandlePocketCollision, this, _1);

	// Create the pockets
	for (int i = 0; i < 6; i++)
	{
		GameObject* pocket = _Game->AddGameObject("Pocket_" + std::to_string(i));


		SphereCollider* pocketCollider = pocket->AddComponent<SphereCollider>();
		RigidBody* pocketRigidbody = pocket->AddComponent<RigidBody>();

		pocketCollider->SetRadius(4);
		pocketRigidbody->SetMass(0.0f);
		pocketRigidbody->SetIsMovable(false);

		/*
		SimpleMaterial* pocketMaterial = pocket->AddComponent<SimpleMaterial>();
		MeshRenderer* pocketMeshRenderer = pocket->AddComponent<MeshRenderer>();
		pocketMeshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
		pocketMeshRenderer->SetMaterial(pocketMaterial);
		pocketMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));
		*/

		pocket->GetTransform()->SetScale(vec3(4, 4, 4));

		// Add the HandlePocketCollision function pointer to the event listener of the pocket.
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

		_PocketColliders.push_back(pocket);
	}
}

// Places the pool balls into starting position
void BilliardGameManager::PreparePoolBalls(int rows)
{
	// Resets the score
    _Score = 0;

	// Creates the Cueball object if it does not exist.
    if (_Cueball == nullptr)
    {
		_Cueball = _Game->AddGameObject("Cueball");
		SimpleMaterial* material = _Cueball->AddComponent<SimpleMaterial>();
		MeshRenderer* meshRenderer = _Cueball->AddComponent<MeshRenderer>();
		SphereCollider* collider = _Cueball->AddComponent<SphereCollider>();
		RigidBody* rigidBody = _Cueball->AddComponent<RigidBody>();

        collider->SetRadius(BALL_SIZE* 0.5f);

        rigidBody->SetMass(1.0f);

        meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
        meshRenderer->SetMaterial(material);

		material->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));
    }

	// Puts the Cueball in the proper position and makes sure it is at rest
	_Cueball->GetTransform()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
	_Cueball->GetTransform()->SetScale(vec3(BALL_SIZE));
	_Cueball->GetComponent<RigidBody>()->SetVelocity(vec3(0));
	_Cueball->GetComponent<RigidBody>()->SetAcceleration(vec3(0));
	_Cueball->SetActive(true);

	// Remove existing numbered balls to create them a new
    for (GameObject* ball : _Balls)
    {
        _Game->Destroy(ball);
    }
    _Balls.clear();

    // Creates and place the numbered balls
    for (int row = 1; row <= rows; row++)
    {
        for (int i = 0; i < row; i++)
        {
            GameObject* ball = _Game->AddGameObject("Ball_" + std::to_string(row) + '_' + std::to_string(i));
            Transform* transform = ball->GetTransform();
            SimpleMaterial* material = ball->AddComponent<SimpleMaterial>();
            MeshRenderer* meshRenderer = ball->AddComponent<MeshRenderer>();
            SphereCollider* collider = ball->AddComponent<SphereCollider>();
            RigidBody* rigidBody = ball->AddComponent<RigidBody>();

            collider->SetRadius(BALL_SIZE* 0.5f);
            rigidBody->SetMass(1.0f);

            meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
            meshRenderer->SetMaterial(material);

			// Finds the texture of the ball based on the current one selected
            std::string texName = "Textures\\" + std::to_string((_Balls.size()) % 15 + 1) + "-Ball.png";
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

            _Balls.push_back(ball);
        }
    }

	// Resets the cameras
    _ActiveCamera = _camTopDown->GetComponent<Camera>();
	_TargetBallIndex = 0;

	_camFollower->GetComponent<SmoothFollow>()->SetTarget(_Cueball->GetTransform());
	_camTracker->GetComponent<Tracker>()->SetTarget(_Cueball->GetTransform());


	// Line rendering
    GameObject* line = _Game->AddGameObject("Line");
    LineMaterial* lineMaterial = line->AddComponent<LineMaterial>();
    MeshRenderer* lineMeshRenderer = line->AddComponent<MeshRenderer>();

    lineMeshRenderer->SetMaterial(lineMaterial);
}

void BilliardGameManager::Update()
{
	_IsTableSettled = true;
    for (unsigned int i = 0; i < _Balls.size(); i++)
    {
		// Checks if the table is settled
		if (!_Balls[i]->GetComponent<RigidBody>()->IsAtRest())
		{
			_IsTableSettled = false;
		}

		// Checks if any of the balls exceeded bounds
		vec3 position = _Balls[i]->GetTransform()->GetPosition();
        if (glm::abs(position.x) > 50.0f
            || glm::abs(position.z) > 25.0f)
        {
			_Game->Destroy(_Balls[i]);
			_Balls.erase(_Balls.begin() + i);
            i--;
        }
    }
	_IsTableSettled = _IsTableSettled && _Cueball->GetComponent<RigidBody>()->IsAtRest();

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
        _ActiveCamera = _camTopDown->GetComponent < Camera>();
    }
    else if (Input::WasKeyPressed(Key::Num2))
    {
		_ActiveCamera = _camFollower->GetComponent < Camera>();
    }
    else if (Input::WasKeyPressed(Key::Num3))
    {
		_ActiveCamera = _camTracker->GetComponent < Camera>();
    }
    else if (Input::WasKeyPressed(Key::Num4))
    {
		_ActiveCamera = _camFPS->GetComponent < Camera>();
    }

	// Change camera target
    if (Input::WasKeyReleased(Key::Up))
    {
		_TargetBallIndex = (_TargetBallIndex + 1 + _Balls.size()) % _Balls.size();

		_camFollower->GetComponent<SmoothFollow>()->SetTarget(_Balls[_TargetBallIndex]->GetTransform());
        _camTracker->GetComponent<Tracker>()->SetTarget(_Balls[_TargetBallIndex]->GetTransform());
    }
    else if (Input::WasKeyReleased(Key::Down))
    {
		_TargetBallIndex = (_TargetBallIndex - 1 + _Balls.size()) % _Balls.size();

		_camFollower->GetComponent<SmoothFollow>()->SetTarget(_Balls[_TargetBallIndex]->GetTransform());
		_camTracker->GetComponent<Tracker>()->SetTarget(_Balls[_TargetBallIndex]->GetTransform());
    }
    else if (Input::WasKeyReleased(Key::Tilde))
    {
        _camFollower->GetComponent<SmoothFollow>()->SetTarget(_Cueball->GetTransform());
		_camTracker->GetComponent<Tracker>()->SetTarget(_Cueball->GetTransform());
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
		mousePosDifference *= 4.0f;
		glm::clamp(mousePosDifference, -MAX_FORCE, MAX_FORCE);
		
        _Cueball->GetComponent<RigidBody>()->AddForce(vec3(mousePosDifference.x, 0, mousePosDifference.y));
    }


	// Sets the text
	_TextRenderer->SetText(std::to_string(_Score) + '/' + std::to_string(_Balls.size())
		+ "\nIs table settled: " + (_IsTableSettled ? "Yes" : "No")
		+ "\nCamera Mode: " + _ActiveCamera->GetGameObject()->GetName()
		);
}

/*
	This is called when a ball collides with a pocket colliders
	This is subscribed to the "OnCollide" event of the pocket colliders
*/
void BilliardGameManager::HandlePocketCollision(GameObject* gameObject)
{
	string name = gameObject->GetName();

	// Checks if game object is the Cueball
	if (name == "Cueball")
    {
		_Cueball->GetComponent<RigidBody>()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
		if (_Score == _Balls.size())
		{
			std::printf("You Win");
			PreparePoolBalls();
		}
		else
		{
			std::printf("Cueball entered pocket before the others.");
			PreparePoolBalls();
		}
    }
	// Checks if the game object is a numbered ball
	else if (name.substr(0,4) == "Ball")	// The first four characters of the name of the numbered balls is "Ball"
	{
		// Place ball over wall
		gameObject->GetTransform()->SetPosition(vec3(-50 + _Score * BALL_SIZE, 10, -25));
		_Score++;
		gameObject->GetComponent<RigidBody>()->SetVelocity(vec3(0));

		// Removes object from simulation
		Physics::UnregisterRigidbody(gameObject->GetComponent<RigidBody>());
	}
}

GameObject* BilliardGameManager::GetCueball(){ return _Cueball; }
vector<GameObject*> BilliardGameManager::GetNumberedPoolBalls() { return _Balls; }

Camera* BilliardGameManager::GetActiveCamera() { return _ActiveCamera; }

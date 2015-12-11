#include "BilliardGameManager.h"
#include "Time.hpp"
#include "Input.hpp"
#include "Physics.hpp"

#define BALL_SIZE 2.0f

Input* inputController;
vec2 mouseClickPos = inputController->GetMousePosition();

BilliardGameManager::BilliardGameManager()
{
    _game = Game::GetInstance();

	// Add a test text renderer
	{
		auto go = _game->AddGameObject("TableTextRenderer");
		auto tm = go->AddComponent<TextMaterial>();
		_TextRenderer = go->AddComponent<TextRenderer>();

		std::shared_ptr<Font> font = std::make_shared<Font>();
		assert(font->LoadFromFile("Fonts\\OpenSans-Regular.ttf"));
		_TextRenderer->SetFont(font);
		_TextRenderer->SetFontSize(16U);
		tm->SetTextColor(vec4(0, 0, 0, 1));

		go->GetTransform()->SetPosition(glm::vec3(500, 10, 0));
	}
    
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
        BoxCollider* tableFloorCollider = tableFloor->AddComponent<BoxCollider>();
        MeshRenderer* tableFloorMeshRenderer = tableFloor->AddComponent<MeshRenderer>();
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
            BoxCollider* tableWallCollider = tableWall->AddComponent<BoxCollider>();
            MeshRenderer* tableWallMeshRenderer = tableWall->AddComponent<MeshRenderer>();
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


	std::function<void(GameObject*)> func = std::bind(&BilliardGameManager::HandlePocketCollision, this, _1);

    // Create the test pocket
	for (int i = 0; i < 6; i++)
	{
		GameObject* pocket = _game->AddGameObject("Pocket_" + std::to_string(i));
		
		
		SphereCollider* pocketCollider = pocket->AddComponent<SphereCollider>();
		RigidBody* pocketRigidbody = pocket->AddComponent<RigidBody>();

		pocketCollider->SetRadius(4);
		pocketRigidbody->SetMass(0.0f);
		pocketRigidbody->SetIsMovable(false);


		/*SimpleMaterial* pocketMaterial = pocket->AddComponent<SimpleMaterial>();
		MeshRenderer* pocketMeshRenderer = pocket->AddComponent<MeshRenderer>();
		pocketMeshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
		pocketMeshRenderer->SetMaterial(pocketMaterial);
		pocketMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));
		*/

		pocket->GetTransform()->SetScale(vec3(4, 4, 4));

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
        cueball = _game->AddGameObject("Cueball");
        SimpleMaterial* material = cueball->AddComponent<SimpleMaterial>();
        MeshRenderer* meshRenderer = cueball->AddComponent<MeshRenderer>();
        SphereCollider* collider = cueball->AddComponent<SphereCollider>();
        RigidBody* rigidBody = cueball->AddComponent<RigidBody>();

        collider->SetRadius(BALL_SIZE* 0.5f);

        rigidBody->SetMass(1.0f);

        meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
        meshRenderer->SetMaterial(material);

		material->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));
    }


    cueball->GetTransform()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
    cueball->GetTransform()->SetScale( vec3( BALL_SIZE ) );
    cueball->GetComponent<RigidBody>()->SetVelocity( vec3( 0 ) );
    cueball->GetComponent<RigidBody>()->SetAcceleration( vec3( 0 ) );
	cueball->SetActive(true);

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
            SphereCollider* collider = ball->AddComponent<SphereCollider>();
            RigidBody* rigidBody = ball->AddComponent<RigidBody>();

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



    GameObject* line = _game->AddGameObject("Line");
    LineMaterial* lineMaterial = line->AddComponent<LineMaterial>();
    MeshRenderer* lineMeshRenderer = line->AddComponent<MeshRenderer>();

    lineMeshRenderer->SetMaterial(lineMaterial);



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

    for (auto i = 0; i < balls.size(); i++)
    {
        vec3 position = balls[i]->GetTransform()->GetPosition();
        if (glm::abs(position.x) > 50.0f
            || glm::abs(position.z) > 25.0f)
        {
            _game->Destroy(balls[i]);
            balls.erase(balls.begin() + i);
            i--;
        }
    }


    if (Input::WasKeyReleased(Key::Space))
    {
        cueball->GetComponent<RigidBody>()->AddForce(vec3(4000.0f, 0, 0));
    }
    else if (Input::WasKeyReleased(Key::Enter))
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

	_TextRenderer->SetText(std::to_string(score) + '/' + std::to_string(balls.size()) + "   Is table settled: " + (_Ready ? "True" : "False"));
}

void BilliardGameManager::HandlePocketCollision(GameObject* gameObject)
{
	string name = gameObject->GetName();
	if (name == "Cueball")
    {
		cueball->GetComponent<RigidBody>()->SetPosition(vec3(-11, BALL_SIZE * 0.5f, 0));
		if (score == balls.size())
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
	else if (name.substr(0,4) == "Ball")
	{
		gameObject->GetTransform()->SetPosition(vec3(-50 + score * BALL_SIZE, 4, -25));
		score++;
		gameObject->GetComponent<RigidBody>()->SetVelocity(vec3(0));
		Physics::UnregisterRigidbody(gameObject->GetComponent<RigidBody>());
	}
}


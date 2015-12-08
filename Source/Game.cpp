#include "Game.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include <GLFW/glfw3.h>
#include "Texture2D.hpp"
#include "MeshLoader.hpp"
#include "RigidBody.h"
#include "Physics.hpp"
#include "RenderManager.hpp"

#define BALL_SIZE 2.0f

std::shared_ptr<Game> Game::_instance = nullptr;

CameraManager* cameraManager;

std::vector<GameObject*> balls = std::vector<GameObject*>();

GameObject* table;


static void APIENTRY MyGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
    if (source == GL_DEBUG_SOURCE_API)
    {
        std::cout << message << std::endl;
    }
}

// Creates a new game
Game::Game()
    : _window( nullptr )
    , _clearColor( 0.0f, 0.0f, 0.0f, 1.0f )
{
    // Create the window
    _window = std::make_shared<GameWindow>( 1280, 720, "Billy's 3D Billiards" );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
#if defined( _DEBUG ) || defined( DEBUG )
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
    if ( glDebugMessageCallback )
    {
        glDebugMessageCallback( MyGLCallback, nullptr );
    }
#endif


    // Add a test text renderer
    {
        auto go = AddGameObject( "TestTextRenderer" );
        auto tm = go->AddComponent<TextMaterial>();
        auto tr = go->AddComponent<TextRenderer>();

        std::shared_ptr<Font> font = std::make_shared<Font>();
        assert( font->LoadFromFile( "Fonts\\OpenSans-Regular.ttf" ) );
        tr->SetFont( font );
        tr->SetFontSize( 32U );
        tr->SetText( "Hello, world!" );
        tm->SetTextColor( vec4( 1, 0, 0, 1 ) );

        go->GetTransform()->SetPosition( glm::vec3( 100, 100, 0 ) );
    }


    // Create the table
    {
        table = AddGameObject("Table");
        SimpleMaterial* tableMaterial = table->AddComponent<SimpleMaterial>();
        MeshRenderer* tableMeshRenderer = table->AddComponent<MeshRenderer>();

        tableMeshRenderer->SetMesh(MeshLoader::Load("Models\\Pool_Table.fbx"));
        tableMeshRenderer->SetMaterial(tableMaterial);
        tableMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Rocks.jpg"));
    }

    // Create the table colliders
    {
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

            //tableFloorMaterial->SetTexture("MyTexture", Texture2D::FromFile("Textures\\Cue-Ball.png"));
        }
    }

    // Create the cue ball in its own scope to prevent accidental referencing of other things
    {
        GameObject* cueball = AddGameObject("CueBall");
        SimpleMaterial* material = cueball->AddComponent<SimpleMaterial>();
        MeshRenderer* meshRenderer = cueball->AddComponent<MeshRenderer>();
        RigidBody* rigidBody = cueball->AddComponent<RigidBody>();
        SphereCollider* collider = cueball->AddComponent<SphereCollider>();

        collider->SetRadius(0.5f);

        rigidBody->SetMass(1.0f);

        meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
        meshRenderer->SetMaterial(material);

        material->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

        cueball->GetTransform()->SetPosition(vec3(0.0f, BALL_SIZE * 0.5f, -11));
        rigidBody->AddForce(vec3(0, 0, 20.0f));

        balls.push_back(cueball);
    }

    // Create all of the balls
    for (int row = 1; row <= 5; row++)
    {
        for (int i = 0; i < row; i++)
        {
            GameObject* ball = AddGameObject("Ball_" + std::to_string(row) + '_' + std::to_string(i));
            Transform* transform = ball->GetTransform();
            SimpleMaterial* material = ball->AddComponent<SimpleMaterial>();
            MeshRenderer* meshRenderer = ball->AddComponent<MeshRenderer>();
            RigidBody* rigidBody = ball->AddComponent<RigidBody>();
            SphereCollider* collider = ball->AddComponent<SphereCollider>();

            rigidBody->SetMass(1.0f);

            meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
            meshRenderer->SetMaterial(material);
            
            std::string texName = "Textures\\" + std::to_string( ( balls.size() - 1) % 15 + 1 ) + "-Ball.png";
            std::cout << "Loading " << texName << "... ";

            std::shared_ptr<Texture2D> texture = Texture2D::FromFile( texName );
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

            balls.push_back(ball);
        }
    }

    
    /*{
        GameObject* testBox = AddGameObject("testBox");
        SimpleMaterial* boxMaterial = testBox->AddComponent<SimpleMaterial>();
        MeshRenderer* testBoxMeshRenderer = testBox->AddComponent<MeshRenderer>();
        RigidBody* testBoxRigidBody = testBox->AddComponent<RigidBody>();
        BoxCollider* testBoxCollider = testBox->AddComponent<BoxCollider>();

        testBoxCollider->SetSize(vec3(1, 1, 1));

        testBoxRigidBody->SetMass(100.0f);

        testBoxMeshRenderer->SetMesh(MeshLoader::Load("Models\\Cube.obj"));
        testBoxMeshRenderer->SetMaterial(boxMaterial);

        //boxMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

        testBox->GetTransform()->SetPosition(vec3(0.25f, 0.5f, -2.0f));
    }*/

    /*for (int i = 0; i < 10; i++)
    {
        GameObject* testBox = AddGameObject("testBox_" + std::to_string(i));
        SimpleMaterial* boxMaterial = testBox->AddComponent<SimpleMaterial>();
        MeshRenderer* testBoxMeshRenderer = testBox->AddComponent<MeshRenderer>();
        RigidBody* testBoxRigidBody = testBox->AddComponent<RigidBody>();
        BoxCollider* testBoxCollider = testBox->AddComponent<BoxCollider>();

        testBoxCollider->SetSize(vec3(1, 1, 1));

        testBoxRigidBody->SetMass(100.0f);

        testBoxMeshRenderer->SetMesh(MeshLoader::Load("Models\\Cube.obj"));
        testBoxMeshRenderer->SetMaterial(boxMaterial);

        //boxMaterial->SetMyTexture(Texture2D::FromFile("Textures\\Cue-Ball.png"));

        testBox->GetTransform()->SetPosition(vec3(-7.5f + i * 1.25f, 0.5f, 10.0f));
    }*/
    
    // Resize all of the balls
    for (auto& ball : balls)
    {
        SphereCollider* collider = ball->GetComponent<SphereCollider>();
        Transform* transform = ball->GetTransform();

        collider->SetRadius(BALL_SIZE * 0.5f);
        transform->SetScale(vec3(BALL_SIZE));
    }

#pragma region Camera
    // Camera Manager
    GameObject* cameraManagerObject = AddGameObject("CameraManager");
    cameraManager = cameraManagerObject->AddComponent<CameraManager>();

    // Default Camera
    GameObject* cameraObject = cameraManagerObject->AddChild("CameraObject");
    Camera* camera = cameraObject->AddComponent<Camera>();
    camera->SetPosition(vec3(0, 50, 30));
    camera->LookAtPosition(vec3(0, 0, 0));
    cameraManager->AddCamera(camera);

    // Smooth Follow Camera
    GameObject* cameraObjectSmoothFollower = AddGameObject("CameraObjectSmoothFollow");
    Camera* cameraSmoothFollower = cameraObjectSmoothFollower->AddComponent<Camera>();
    cameraSmoothFollower->SetPosition(vec3(-4, 4, -4));
    SmoothFollow* smoothFollow = cameraObjectSmoothFollower->AddComponent<SmoothFollow>();
    smoothFollow->SetTarget(balls[0]->GetTransform());
    cameraManager->AddCamera(cameraSmoothFollower);

    // Tracker Camera
    GameObject* cameraObjectTracker = AddGameObject("CameraObjectTracker");
    Camera* cameraTracker = cameraObjectTracker->AddComponent<Camera>();
    cameraTracker->SetPosition(vec3(0, 50, 30));
    Tracker* tracker = cameraObjectTracker->AddComponent<Tracker>();
    tracker->SetTarget(balls[0]->GetTransform());
    cameraManager->AddCamera(cameraTracker);

    // FPS Camera
    GameObject* cameraObjectFPS = AddGameObject("CameraObjectFPS");
    Camera* cameraFPS = cameraObjectFPS->AddComponent<Camera>();
    cameraFPS->SetPosition(vec3(0, 50, 30));
    FPSController* fPSController = cameraObjectFPS->AddComponent<FPSController>();
    cameraManager->AddCamera( cameraFPS );
#pragma endregion

    std::cout << "Press SPACE to apply a small force to the cue ball" << std::endl;
    std::cout << "Press ENTER to apply a large force to the cue ball" << std::endl;
}

// Destroys the game instance
Game::~Game()
{
    _window = nullptr;
}

// Adds a game object to the game
GameObject* Game::AddGameObject( const std::string& name )
{
    // Check if there's already a game object with the given name
    auto search = _gameObjectCache.find( name );
    if ( search != _gameObjectCache.end() )
    {
        return search->second.get();
    }

    // Create the game object
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>( name );

    // Record the game object
    _gameObjects.push_back( go );
    _gameObjectCache[ name ] = go;

    return go.get();
}

// Draws the game
void Game::Draw()
{
    /* for (auto& object : _gameObjects)
    {
        if (object->GetActive())
            object->Draw();
    } */
    RenderManager::Draw();
}

// Get the game instance
Game* Game::GetInstance()
{
    if ( !_instance )
    {
        _instance.reset( new Game() );
    }
    return _instance.get();
}

// Get the clear color
glm::vec4 Game::GetClearColor() const
{
    return _clearColor;
}

// Runs the game
void Game::Run()
{
    Time::Start();

    // Set the window to visible then begin the game loop
    _window->SetVisible( true );
    while ( _window->IsOpen() )
    {
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Update and draw the game
        Update();
        Draw();

        // Update the time values
        Time::Update();

        // Poll for events and swap the buffers
        _window->SwapBuffers();
        _window->PollEvents();
    }
}

// Set the clear color
void Game::SetClearColor( float r, float g, float b, float a )
{
    SetClearColor( glm::vec4( r, g, b, a ) );
}

// Set the clear color
void Game::SetClearColor( const glm::vec4& value )
{
    _clearColor = value;
    glClearColor( _clearColor.r,
                  _clearColor.g,
                  _clearColor.b,
                  _clearColor.a );
}

// Updates the game
void Game::Update()
{
    static int frameCount = 0;
    static float tickCount = 0.0f;
    static bool first = true;

    tickCount += Time::GetElapsedTime();
    ++frameCount;

    // counts Frames per second
    if ( tickCount >= 1.0f )
    {
        std::string title = "Billy's 3D Billiards";

        title += "    |    " + std::to_string( frameCount ) + " FPS";
        _window->SetTitle( title );

        frameCount = 0;
        tickCount -= 1.0f;
    }

    // Sets materials on Objects
    for (auto& object : _gameObjects)
    {
        if (object->GetActive())
        {
            Material* material = object->GetComponentOfType<Material>();
            if (material)
            {
                material->ApplyCamera(cameraManager->GetActiveCamera());
            }
            object->Update();
        }
    }
    
    if (Input::WasKeyPressed(Key::Space))
    {
        balls[0]->GetComponent<RigidBody>()->AddForce(vec3(0, 0, 4000.0f));
        first = false;
    }
    else if (Input::WasKeyPressed(Key::Enter))
    {
        balls[0]->GetComponent<RigidBody>()->AddForce(vec3(0, 0, 10000.0f));
        first = false;
    }


    // Sets positons
    //vec3 cubePosition(glm::sin(Time::GetTotalTime() / 4) * 4, 0, glm::cos(Time::GetTotalTime() / 4) * 4);
    //vec3 spherePosition = vec3(-5.0f, abs(sin(Time::GetTotalTime()) * 4) , -5);
    //vec3 otherSpherePosition = vec3(5.0f, abs(cos(Time::GetTotalTime()) * 4), -5);
    
    /*
    // get transformations then set positons
    cube->GetTransform()->SetPosition(cubePosition);
    sphere->GetComponent<RigidBody>()->SetAcceleration(vec3(1.0f, 1.0f, 1.0f));
    sphere->GetTransform()->SetPosition(vec3(1.0f,1.0f,1.0f));
    otherSphere->GetTransform()->SetPosition(vec3(2.0f, 2.0f, 2.0f));

    // Test positions
    testSphere->GetTransform()->SetPosition(vec3(5.0f, 0.0f, 0.0f));	
    testSphere->GetComponent<RigidBody>()->SetPosition(testSphere->GetTransform()->GetPosition());
    testSphere->GetComponent<RigidBody>()->SetVelocity(vec3(-1.0f, 0.0f, 0.0f));
    testSphere->GetComponent<RigidBody>()->SetAcceleration(vec3(-.5f, .0f, .0f));


    otherTestSphere->GetTransform()->SetPosition(vec3(-5.0f, 0.0f, 0.0f));
    otherTestSphere->GetComponent<RigidBody>()->SetPosition(otherTestSphere->GetTransform()->GetPosition());
    otherTestSphere->GetComponent<RigidBody>()->SetVelocity(vec3(1.0f, 0.0f, 0.0f));
    otherTestSphere->GetComponent<RigidBody>()->SetAcceleration(vec3(.5f, .0f, .0f));

    // Test for sphere on box
    boxSphereTest->GetTransform()->SetPosition(vec3(-5.0f, 0.0f, 0.0f));
    boxSphereTest->GetComponent<RigidBody>()->SetPosition(boxSphereTest->GetTransform()->GetPosition());
    boxSphereTest->GetComponent<RigidBody>()->SetVelocity(vec3(1.0f, 0.0f, 0.0f));
    boxSphereTest->GetComponent<RigidBody>()->SetAcceleration(vec3(.5f, .0f, .0f));
    
    box->GetTransform()->SetPosition(vec3(0.0f, 0.0f, 0.0f));
    */

    // Update the physics
    Time::Update();
    Physics::Update();
    Input::Update(_window->_window);

    // If escape is being pressed, then we should close the window
    if ( Input::WasKeyPressed( Key::Escape ) )
    {
        _window->Close();
    }
}

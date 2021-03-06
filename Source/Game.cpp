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
//#define USE_OPENGL_DEBUG

std::shared_ptr<Game> Game::_instance = nullptr;

CameraManager* cameraManager;

TextRenderer* tr;



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
#if defined( _DEBUG ) && defined( USE_OPENGL_DEBUG )
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
    if ( glDebugMessageCallback )
    {
        glDebugMessageCallback( MyGLCallback, nullptr );
    }
#endif

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

// Destroys the given game object
bool Game::Destroy( GameObject* gameObject )
{
    if ( !gameObject )
    {
        return false;
    }

    // Find the game object in the cache
    auto search = _gameObjectCache.find( gameObject->GetName() );
    if ( search != _gameObjectCache.end() )
    {
        _gameObjectCache.erase( gameObject->GetName() );
    }
    else
    {
        return false;
    }

    // Now remove the game object from the list
    for ( auto iter = _gameObjects.begin(); iter != _gameObjects.end(); ++iter )
    {
        if ( iter->get() == gameObject )
        {
            _gameObjects.erase( iter );
            break;
        }
    }

    return true;
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
	// Add a test text renderer
	{
		auto go = AddGameObject("TestTextRenderer");
		auto tm = go->AddComponent<TextMaterial>();
		tr = go->AddComponent<TextRenderer>();

		std::shared_ptr<Font> font = std::make_shared<Font>();
		assert(font->LoadFromFile("Fonts\\OpenSans-Regular.ttf"));
		tr->SetFont(font);
		tr->SetFontSize(12U);
		tr->SetText("Hello, world!");
		tm->SetTextColor(vec4(1, 0, 0, 1));

		go->GetTransform()->SetPosition(glm::vec3(5, 5, 0));
	}

	gameManager = std::make_shared<BilliardGameManager>();
	gameManager->CreateTable();
	gameManager->PreparePoolBalls();


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
        Physics::Update();
        Input::Update( _window->_window );

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

    float elapsedTime = Time::GetElapsedTime();
    tickCount += elapsedTime;
    ++frameCount;

    if ( tr )
    {
        tr->SetText( std::to_string( elapsedTime ) + "ms\t" + std::to_string( tickCount ) + "ms\t" + std::to_string( frameCount ) );
    }

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
                material->ApplyCamera(gameManager->GetActiveCamera());
            }
            object->Update();
        }
    }
    

    gameManager->Update();


    // If escape is being pressed, then we should close the window
    if ( Input::WasKeyPressed( Key::Escape ) )
    {
        _window->Close();
    }


    if ( Input::WasKeyPressed( Key::T ) )
    {
        Destroy( tr->GetGameObject() );
        tr = nullptr;
    }
}

#include "Game.hpp"
#include "Time.hpp"
#include <GLFW/glfw3.h>
#include "SimpleMaterial.hpp"
#include "Texture2D.hpp"
#include "MeshRenderer.hpp"
#include "MeshLoader.hpp"

std::shared_ptr<Game> Game::_instance = nullptr;

std::shared_ptr<Texture2D> texture;

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MyGLCallback, nullptr);

	GameObject* imageTest = AddGameObject("ImageTest");
	SimpleMaterial* material = imageTest->AddComponent<SimpleMaterial>();
	MeshRenderer* meshRenderer = imageTest->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(MeshLoader::Load("Models\\Sphere.obj"));
	meshRenderer->SetMaterial(material);

	texture = Texture2D::FromFile("Textures\\Test_Texture.png");

	material->SetTexture("textureSampler", texture);
	material->SetVec3("tint", glm::vec3(1, 0, 1));
	material->SetMatrix("View", glm::lookAt(vec3(4, 0, 0), vec3(0), vec3(0, 1, 0)));
	material->SetMatrix("Projection", glm::perspective(glm::quarter_pi<float>(), 1.33f, 0.001f, 1000.0f));
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
	for (auto& object : _gameObjects)
	{
		object->Draw();
	}
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

    tickCount += Time::GetElapsedTime();
    ++frameCount;

    if ( tickCount >= 1.0f )
    {
        std::string title = "Billy's 3D Billiards";

        title += "    |    " + std::to_string( frameCount ) + " FPS";
        _window->SetTitle( title );

        frameCount = 0;
        tickCount -= 1.0f;
    }


	for (auto& object : _gameObjects)
	{
		object->GetTransform()->SetRotation(glm::vec3(0, Time::GetTotalTime(), 0));
		object->Update();
	}


    // If escape is being pressed, then we should close the window
    if ( glfwGetKey( glfwGetCurrentContext(), GLFW_KEY_ESCAPE ) )
    {
        _window->Close();
    }
}

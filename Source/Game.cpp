#include "Game.hpp"
#include "Time.hpp"
#include <GLFW/glfw3.h>

std::shared_ptr<Game> Game::_instance = nullptr;

// Creates a new game
Game::Game()
    : _window( nullptr )
    , _clearColor( 0.0f, 0.0f, 0.0f, 1.0f )
{
    // Create the window
    _window = std::make_shared<GameWindow>( 1280, 720, "Billy's 3D Billiards" );
}

// Destroys the game instance
Game::~Game()
{
    _window = nullptr;
}

// Draws the game
void Game::Draw()
{
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
}

#pragma warning( disable:4800 ) // Ignore int->bool cast

#include "GameWindow.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>
#if defined( DEBUG ) || defined( _DEBUG )
#   include <iostream>
#endif

// Helper macro for our window
#define _myWindow static_cast<GLFWwindow*>( _window )

// A cache containing all windows
static std::unordered_map<GLFWwindow*, GameWindow*> WindowCache;

// Gets the center of a monitor
static glm::ivec2 GetMonitorCenter( GLFWmonitor* monitor )
{
    const GLFWvidmode* videoMode = glfwGetVideoMode( monitor );
    return glm::ivec2( videoMode->width / 2, videoMode->height / 2 );
}

// Gets the center of the primary monitor
static glm::ivec2 GetPrimaryMonitorCenter()
{
    return GetMonitorCenter( glfwGetPrimaryMonitor() );
}

// Creates a new game window
GameWindow::GameWindow( int width, int height, const std::string& title )
    : _window( nullptr )
{
    // Set the GLFW hints that we want
    glfwDefaultWindowHints();
    glfwWindowHint( GLFW_RESIZABLE, false );
    glfwWindowHint( GLFW_VISIBLE,   false );

    // Create the window
    GLFWwindow* window = glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr );
    if ( window )
    {
        // If the window was created, center it
        glm::ivec2 center = GetPrimaryMonitorCenter();
        glfwSetWindowPos( window, center.x - width / 2, center.y - height / 2 );

        // Register us in the cache
        WindowCache[ window ] = this;

        // Set our local variables
        _window = window;
        _title  = std::make_shared<std::string>( title );


        // Make the window the current context
        glfwMakeContextCurrent( window );

        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum initialized = glewInit();
        if ( initialized != GLEW_OK )
        {
#if defined( DEBUG ) || defined( _DEBUG )
            const char* errorMessage = reinterpret_cast<const char*>( glewGetErrorString( initialized ) );
            std::cout << "Failed to initialize GLEW. Reason: " << errorMessage << std::endl;
#endif
        }
    }
#if defined( DEBUG ) || defined( _DEBUG )
    else
    {
        std::cout << "Failed to create " << width << "x" << height << " window with title '" << title << "'." << std::endl;
    }
#endif
}

// Destroys this game window
GameWindow::~GameWindow()
{
    _window = nullptr;
}

// Get the active window on the current thread
GameWindow* GameWindow::GetCurrentWindow()
{
    auto search = WindowCache.find( glfwGetCurrentContext() );
    if ( search != WindowCache.end() )
    {
        return search->second;
    }
    return nullptr;
}

// Gets this window's title
std::string GameWindow::GetTitle() const
{
    return *_title;
}

// Gets this window's width
int GameWindow::GetWidth() const
{
    glm::ivec2 size;
    glfwGetWindowSize( _myWindow, &size.x, &size.y );
    return size.x;
}

// Gets this window's height
int GameWindow::GetHeight() const
{
    glm::ivec2 size;
    glfwGetWindowSize( _myWindow, &size.x, &size.y );
    return size.y;
}

// Checks to see if this window is open
bool GameWindow::IsOpen() const
{
    return !glfwWindowShouldClose( _myWindow );
}

// Checks to see if this window is visible
bool GameWindow::IsVisible() const
{
    return static_cast<bool>( glfwGetWindowAttrib( _myWindow, GLFW_VISIBLE ) );
}

// Closes this window
void GameWindow::Close()
{
    glfwSetWindowShouldClose( _myWindow, true );
}

// Poll and process events
void GameWindow::PollEvents()
{
    glfwPollEvents();
}

// Sets the window's title
void GameWindow::SetTitle( const std::string& value )
{
    *_title = value;
    glfwSetWindowTitle( _myWindow, _title->c_str() );
}

// Sets whether or not this window is visible
void GameWindow::SetVisible( bool value )
{
    if ( value ) glfwShowWindow( _myWindow );
    else         glfwHideWindow( _myWindow );
}

// Swap the underlying buffers for this window
void GameWindow::SwapBuffers()
{
    glfwSwapBuffers( _myWindow );
}

// Checks to see if this window is valid
GameWindow::operator bool() const
{
    return ( _window != nullptr );
}

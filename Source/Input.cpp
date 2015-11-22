#include "Input.hpp"
#include <GLFW/glfw3.h>

std::vector<bool> Input::_lastFrame( static_cast<int>( Key::COUNT ), false );
std::vector<bool> Input::_thisFrame( static_cast<int>( Key::COUNT ), false );
glm::vec2 Input::_thisFrameMouse( 0.0f, 0.0f );
glm::vec2 Input::_lastFrameMouse( 0.0f, 0.0f );

// Check if key is down
bool Input::IsKeyDown( Key key )
{
    return _thisFrame[ static_cast<size_t>( key ) ];
}

// Check if key is up
bool Input::IsKeyUp( Key key )
{
    return !IsKeyDown( key );
}

// Get delta mouse position
glm::vec2 Input::GetDeltaMousePosition()
{
    return _thisFrameMouse - _lastFrameMouse;
}

// Get mouse position
glm::vec2 Input::GetMousePosition()
{
    return _thisFrameMouse;
}

// Update input keys
void Input::Update( void* window )
{
    GLFWwindow* context = reinterpret_cast<GLFWwindow*>( window );

    for ( int i = 0; i < static_cast<int>( _thisFrame.size() ); ++i )
    {
        _lastFrame[ i ] = _thisFrame[ i ];
        _thisFrame[ i ] = ( glfwGetKey( context, i ) == GLFW_PRESS );
    }

    _lastFrameMouse = _thisFrameMouse;
    
    double x = 0, y = 0;
    glfwGetCursorPos( context, &x, &y );

    _thisFrameMouse.x = static_cast<float>( x );
    _thisFrameMouse.y = static_cast<float>( y );
}

// Check if key was pressed
bool Input::WasKeyPressed( Key key )
{
    size_t index = static_cast<size_t>( key );
    return _thisFrame[ index ] && !_lastFrame[ index ];
}

// Check if key was released
bool Input::WasKeyReleased( Key key )
{
    size_t index = static_cast<size_t>( key );
    return !_thisFrame[ index ] && _lastFrame[ index ];
}

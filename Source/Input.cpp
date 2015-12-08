#include "Input.hpp"
#include <GLFW/glfw3.h>

std::vector<bool> Input::_lastFrameKeys( static_cast<int>( Key::COUNT ), false );
std::vector<bool> Input::_thisFrameKeys( static_cast<int>( Key::COUNT ), false );
std::array<bool, 3> Input::_lastFrameButtons;
std::array<bool, 3> Input::_thisFrameButtons;
glm::vec2 Input::_thisFrameMouse( 0.0f, 0.0f );
glm::vec2 Input::_lastFrameMouse( 0.0f, 0.0f );

// Check if a button is down
bool Input::IsButtonDown( MouseButton mb )
{
    return _thisFrameButtons[ static_cast<size_t>( mb ) ];
}

// Check if a button is up
bool Input::IsButtonUp( MouseButton mb )
{
    return !IsButtonDown( mb );
}

// Check if key is down
bool Input::IsKeyDown( Key key )
{
    return _thisFrameKeys[ static_cast<size_t>( key ) ];
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

    for ( size_t i = 0; i < _thisFrameKeys.size(); ++i )
    {
        _lastFrameKeys[ i ] = _thisFrameKeys[ i ];
        _thisFrameKeys[ i ] = ( glfwGetKey( context, static_cast<int>( i ) ) == GLFW_PRESS );
    }


    _lastFrameButtons[ 0 ] = _thisFrameButtons[ 0 ];
    _lastFrameButtons[ 1 ] = _thisFrameButtons[ 1 ];
    _lastFrameButtons[ 2 ] = _thisFrameButtons[ 2 ];
    _thisFrameButtons[ static_cast<size_t>( MouseButton::Left   ) ] = glfwGetMouseButton( context, GLFW_MOUSE_BUTTON_LEFT );
    _thisFrameButtons[ static_cast<size_t>( MouseButton::Middle ) ] = glfwGetMouseButton( context, GLFW_MOUSE_BUTTON_MIDDLE );
    _thisFrameButtons[ static_cast<size_t>( MouseButton::Right  ) ] = glfwGetMouseButton( context, GLFW_MOUSE_BUTTON_RIGHT );


    _lastFrameMouse = _thisFrameMouse;
    
    double x = 0, y = 0;
    glfwGetCursorPos( context, &x, &y );

    _thisFrameMouse.x = static_cast<float>( x );
    _thisFrameMouse.y = static_cast<float>( y );
}

// Check if button was pressed
bool Input::WasButtonPressed( MouseButton mb )
{
    size_t index = static_cast<size_t>( mb );
    return _thisFrameButtons[ index ] && !_lastFrameButtons[ index ];
}

// Check if button was released
bool Input::WasButtonReleased( MouseButton mb )
{
    size_t index = static_cast<size_t>( mb );
    return !_thisFrameButtons[ index ] && _lastFrameButtons[ index ];
}

// Check if key was pressed
bool Input::WasKeyPressed( Key key )
{
    size_t index = static_cast<size_t>( key );
    return _thisFrameKeys[ index ] && !_lastFrameKeys[ index ];
}

// Check if key was released
bool Input::WasKeyReleased( Key key )
{
    size_t index = static_cast<size_t>( key );
    return !_thisFrameKeys[ index ] && _lastFrameKeys[ index ];
}

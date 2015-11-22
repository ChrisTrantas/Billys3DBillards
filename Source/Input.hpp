#pragma once

#include "Math.hpp"
#include <vector>

/// <summary>
/// An enumeration of known key values.
/// </summary>
enum class Key
{
    // All values copied and modified from the GLFW header
    Space               = 32,
    Apostrophe          = 39,
    Comma               = 44,
    Minus               = 45,
    Period              = 46,
    Slash               = 47,
    Num0                = 48,
    Num1                = 49,
    Num2                = 50,
    Num3                = 51,
    Num4                = 52,
    Num5                = 53,
    Num6                = 54,
    Num7                = 55,
    Num8                = 56,
    Num9                = 57,
    Semicolon           = 59,
    Equal               = 61,
    A                   = 65,
    B                   = 66,
    C                   = 67,
    D                   = 68,
    E                   = 69,
    F                   = 70,
    G                   = 71,
    H                   = 72,
    I                   = 73,
    J                   = 74,
    K                   = 75,
    L                   = 76,
    M                   = 77,
    N                   = 78,
    O                   = 79,
    P                   = 80,
    Q                   = 81,
    R                   = 82,
    S                   = 83,
    T                   = 84,
    U                   = 85,
    V                   = 86,
    W                   = 87,
    X                   = 88,
    Y                   = 89,
    Z                   = 90,
    LBracket            = 91, 
    Backslash           = 92, 
    RBracket            = 93, 
    Tilde               = 96, 
    Escape              = 256,
    Enter               = 257,
    Tab                 = 258,
    Backspace           = 259,
    Insert              = 260,
    Delete              = 261,
    Right               = 262,
    Left                = 263,
    Down                = 264,
    Up                  = 265,
    PageUp              = 266,
    PageDown            = 267,
    Home                = 268,
    End                 = 269,
    CapsLock            = 280,
    ScrollLock          = 281,
    NumLock             = 282,
    PrintScreen         = 283,
    Pause               = 284,
    F1                  = 290,
    F2                  = 291,
    F3                  = 292,
    F4                  = 293,
    F5                  = 294,
    F6                  = 295,
    F7                  = 296,
    F8                  = 297,
    F9                  = 298,
    F10                 = 299,
    F11                 = 300,
    F12                 = 301,
    F13                 = 302,
    F14                 = 303,
    F15                 = 304,
    F16                 = 305,
    F17                 = 306,
    F18                 = 307,
    F19                 = 308,
    F20                 = 309,
    F21                 = 310,
    F22                 = 311,
    F23                 = 312,
    F24                 = 313,
    F25                 = 314,
    LShift              = 340,
    LControl            = 341,
    LAlt                = 342,
    RShift              = 344,
    RControl            = 345,
    RAlt                = 346,
    
    COUNT
};

/// <summary>
/// Defines a static input class, similar to Unity's.
/// </summary>
class Input
{
    friend class Game;

    // Hide instance methods
    Input() = delete;
    ~Input() = delete;
    Input( const Input& ) = delete;
    Input& operator=( const Input& ) = delete;
    Input( Input&& ) = delete;
    Input& operator=( Input&& ) = delete;

private:
    static std::vector<bool> _lastFrame;
    static std::vector<bool> _thisFrame;
    static glm::vec2 _thisFrameMouse;
    static glm::vec2 _lastFrameMouse;

    /// <summary>
    /// Updates the input keys.
    /// </summary>
    static void Update( void* window );

public:
    /// <summary>
    /// Checks to see if the given key is down.
    /// </summary>
    /// <param name="key">The key.</param>
    static bool IsKeyDown( Key key );

    /// <summary>
    /// Checks to see if the given key is up.
    /// </summary>
    /// <param name="key">The key.</param>
    static bool IsKeyUp( Key key );

    /// <summary>
    /// Gets the delta mouse position.
    /// </summary>
    static glm::vec2 GetDeltaMousePosition();

    /// <summary>
    /// Gets the mouse position.
    /// </summary>
    static glm::vec2 GetMousePosition();

    /// <summary>
    /// Checks to see if the given key was pressed.
    /// </summary>
    /// <param name="key">The key.</param>
    static bool WasKeyPressed( Key key );

    /// <summary>
    /// Checks to see if the given key was released.
    /// </summary>
    /// <param name="key">The key.</param>
    static bool WasKeyReleased( Key key );
};

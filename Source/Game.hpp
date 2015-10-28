#pragma once

#include "GameWindow.hpp"
#include "Math.hpp"
#include <memory>

/// <summary>
/// Defines the game handler.
/// </summary>
class Game
{
    static std::shared_ptr<Game> _instance;

    std::shared_ptr<GameWindow> _window;
    glm::vec4                   _clearColor;

    /// <summary>
    /// Creates a new game.
    /// </summary>
    Game();

    /// <summary>
    /// Updates this game.
    /// </summary>
    void Update();

    /// <summary>
    /// Draws this game.
    /// </summary>
    void Draw();

    // Prevent the copy constructor and assignment operator from being used
    Game( const Game& ) = delete;
    Game& operator=( const Game& ) = delete;

    // Prevent the move constructor and assignment operator from being used
    Game( Game&& ) = delete;
    Game& operator=( Game&& ) = delete;

public:
    /// <summary>
    /// Gets the game instance.
    /// </summary>
    static Game* GetInstance();

    /// <summary>
    /// Destroys the game instance.
    /// </summary>
    ~Game();

    /// <summary>
    /// Gets this game's clear color.
    /// </summary>
    glm::vec4 GetClearColor() const;

    /// <summary>
    /// Runs the game.
    /// </summary>
    void Run();

    /// <summary>
    /// Sets this game's clear color.
    /// </summary>
    /// <param name="r">The red component of the new clear color.</param>
    /// <param name="g">The green component of the new clear color.</param>
    /// <param name="b">The blue component of the new clear color.</param>
    /// <param name="a">The alpha component of the new clear color.</param>
    void SetClearColor( float r, float g, float b, float a );

    /// <summary>
    /// Sets this game's clear color.
    /// </summary>
    /// <param name="value">The new clear color.</param>
    void SetClearColor( const glm::vec4& value );
};
#pragma once

#include "GameObject.hpp"
#include "GameWindow.hpp"
#include "Math.hpp"
#include <memory>
#include <map>
#include <vector>
#include "Components.hpp"
#include "BilliardGameManager.h"


class BilliardGameManager;

/// <summary>
/// Defines the game handler.
/// </summary>
class Game
{
    static std::shared_ptr<Game> _instance;

    std::map<std::string, std::shared_ptr<GameObject>> _gameObjectCache;
    std::vector<std::shared_ptr<GameObject>> _gameObjects;
    std::shared_ptr<GameWindow> _window;
    glm::vec4 _clearColor;

    std::shared_ptr<BilliardGameManager> gameManager;

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
    /// Adds a game object to this scene.
    /// </summary>
    /// <param name="name">The name of the game object.</param>
    GameObject* AddGameObject( const std::string& name );

    /// <summary>
    /// Destroys the given game object.
    /// </summary>
    /// <param name="gameObject">The game object.</param>
    bool Destroy( GameObject* gameObject );

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
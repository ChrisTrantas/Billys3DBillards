#pragma once

#include <string>

/// <summary>
/// Defines a game window.
/// </summary>
class GameWindow
{
    mutable void* _window;
    std::string   _title;

    // Hide the copy constructor and assignment operator
    GameWindow( const GameWindow& ) = delete;
    GameWindow& operator=( const GameWindow& ) = delete;

    // Hide the move constructor and assignment operator
    GameWindow( GameWindow&& ) = delete;
    GameWindow& operator=( GameWindow&& ) = delete;

public:
    /// <summary>
    /// Gets the active window on the current thread.
    /// </summary>
    static GameWindow* GetCurrentWindow();

    /// <summary>
    /// Creates a new game window.
    /// </summary>
    /// <param name="width">The window's initial width.</param>
    /// <param name="height">The window's initial height.</param>
    /// <param name="title">The window's initial title.</param>
    GameWindow( int width, int height, const std::string& title );

    /// <summary>
    /// Destroys this game window.
    /// </summary>
    ~GameWindow();

    /// <summary>
    /// Gets this window's title.
    /// </summary>
    std::string GetTitle() const;

    /// <summary>
    /// Gets this window's width.
    /// </summary>
    int GetWidth() const;

    /// <summary>
    /// Gets this window's height.
    /// </summary>
    int GetHeight() const;

    /// <summary>
    /// Checks to see if this window is open.
    /// </summary>
    bool IsOpen() const;

    /// <summary>
    /// Checks to see if this window is visible.
    /// </summary>
    bool IsVisible() const;

    /// <summary>
    /// Polls for pending events and processes them.
    /// </summary>
    void PollEvents();

    /// <summary>
    /// Sets whether or not this window is visible.
    /// </summary>
    /// <param name="value">True to show the window, false to hide it.</param>
    void SetVisible( bool value );

    /// <summary>
    /// Swaps this window's underlying OpenGL buffers.
    /// </summary>
    void SwapBuffers();

    /// <summary>
    /// Ensures this window is valid.
    /// </summary>
    operator bool() const;
};

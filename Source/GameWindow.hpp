#pragma once

#include <memory>
#include <string>

/// <summary>
/// Defines a game window.
/// </summary>
class GameWindow
{
    mutable void*                _window;
    std::shared_ptr<std::string> _title;

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
    /// Creates a new game window.
    /// </summary>
    /// <param name="other">The other window to copy.</param>
    GameWindow( const GameWindow& other ) = default;

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
    /// Sets this window's title.
    /// </summary>
    /// <param name="value">The new title.</param>
    void SetTitle( const std::string& value );

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
    /// Copies information from the given game window.
    /// </summary>
    /// <param name="other">The window to copy.</param>
    GameWindow& operator=( const GameWindow& other ) = default;

    /// <summary>
    /// Ensures this window is valid.
    /// </summary>
    operator bool() const;
};

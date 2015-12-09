#pragma once

#include "Config.hpp"

/// <summary>
/// Defines a time class similar to Unity's.
/// </summary>
class Time
{
    friend class Game; // Allow the game class to update us

    ImplementStaticClass( Time );

private:
    static double _startTime;
    static double _lastFrame;
    static double _currFrame;
    
    /// <summary>
    /// Starts timing.
    /// </summary>
    static void Start();

    /// <summary>
    /// Updates the current time values.
    /// </summary>
    static void Update();

public:
    /// <summary>
    /// Gets the amount of time that has elapsed since the last frame.
    /// </summary>
    static float GetElapsedTime();

    /// <summary>
    /// Gets the total amount of time that has passed since the game has been running.
    /// </summary>
    static float GetTotalTime();
};
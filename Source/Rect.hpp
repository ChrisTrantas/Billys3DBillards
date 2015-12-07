#pragma once

// Can't call this "Rectangle" because of Windows :L

/// <summary>
/// Defines a templated rectangle.
/// </summary>
template<typename T> struct Rect
{
    T X;
    T Y;
    T Width;
    T Height;

    /// <summary>
    /// Creates a new, empty rectangle.
    /// </summary>
    Rect();

    /// <summary>
    /// Creates a new rectangle.
    /// </summary>
    /// <param name="x">The initial X of the rectangle.</param>
    /// <param name="y">The initial X of the rectangle.</param>
    /// <param name="width">The initial width of the rectangle.</param>
    /// <param name="height">The initial height of the rectangle.</param>
    Rect( T x, T y, T width, T height );

    /// <summary>
    /// Destroys this rectangle.
    /// </summary>
    ~Rect();
};

/// <summary>
/// A rectangle with integer components.
/// </summary>
typedef Rect<int> IntRect;

/// <summary>
/// A rectangle with unsigned integer components.
/// </summary>
typedef Rect<unsigned int> UintRect;

/// <summary>
/// A rectangle with float components.
/// </summary>
typedef Rect<float> FloatRect;

#include "Rect.inl"

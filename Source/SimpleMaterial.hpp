#pragma once

#include "Material.hpp"

/// <summary>
/// Defines a simple material.
/// </summary>
class SimpleMaterial : public Material
{
public:
    /// <summary>
    /// Creates a new simple material.
    /// </summary>
    /// <param name="gameObject">The game object this material will belong to.</param>
    SimpleMaterial( GameObject* gameObject );

    /// <summary>
    /// Destroys this simple material.
    /// </summary>
    ~SimpleMaterial();
};

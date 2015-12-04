#pragma once

#include "Component.hpp"

/// <summary>
/// An enumeration of possible collider types.
/// </summary>
enum class ColliderType
{
    Box,
    Sphere
};

/// <summary>
/// Defines the base for all colliders.
/// </summary>
class Collider : public Component
{
protected:
    const ColliderType _colliderType;

    /// <summary>
    /// Creates a new collider component.
    /// </summary>
    /// <param name="gameObject">The game object this component will belong to.</param>
    /// <param name="type">This collider's type.</param>
    Collider( GameObject* gameObject, ColliderType type );

public:
    /// <summary>
    /// Destroys this collider.
    /// </summary>
    virtual ~Collider();

    /// <summary>
    /// Gets this collider's type.
    /// </summary>
    ColliderType GetColliderType() const;

    /// <summary>
    /// Checks to see if this collider collides with the given collider.
    /// </summary>
    /// <param name="other">The other collider.</param>
    bool CollidesWith( Collider* const other );

    /// <summary>
    /// Updates this collider.
    /// </summary>
    void Update() override;
};

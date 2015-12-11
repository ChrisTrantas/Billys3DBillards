#pragma once

#include "Component.hpp"
#include "Math.hpp"

/// <summary>
/// An enumeration of possible collider types.
/// </summary>
enum class ColliderType
{
    Unknown = 0,
    Box     = ( 1 << 0 ),
    Sphere  = ( 1 << 1 )
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
    /// Gets the maximum point of this collider.
    /// </summary>
    virtual glm::vec3 GetMaxPoint() const = 0;

    /// <summary>
    /// Gets the minimum point of this collider.
    /// </summary>
    virtual glm::vec3 GetMinPoint() const = 0;

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

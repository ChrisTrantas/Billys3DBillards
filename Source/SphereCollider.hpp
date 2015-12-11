#pragma once

#include "Collider.hpp"
#include "Math.hpp"

/// <summary>
/// Defines a sphere collider.
/// </summary>
class SphereCollider : public Collider
{
    glm::vec3 _center;
    float _radius;

public:
    /// <summary>
    /// Creates a new sphere collider.
    /// </summary>
    /// <param name="gameObject">The game object this component will belong to.</param>
    SphereCollider( GameObject* gameObject );

    /// <summary>
    /// Destroys this sphere collider.
    /// </summary>
    ~SphereCollider();

    /// <summary>
    /// Gets this sphere's center in local coordinates.
    /// </summary>
    glm::vec3 GetLocalCenter() const;

    /// <summary>
    /// Gets this sphere's center in global coordinates.
    /// </summary>
    glm::vec3 GetGlobalCenter() const;

    /// <summary>
    /// Gets the maximum point of this collider.
    /// </summary>
    virtual glm::vec3 GetMaxPoint() const;

    /// <summary>
    /// Gets the minimum point of this collider.
    /// </summary>
    virtual glm::vec3 GetMinPoint() const;

    /// <summary>
    /// Gets this sphere's radius.
    /// </summary>
    float GetRadius() const;

    /// <summary>
    /// Sets this sphere collider's local center.
    /// </summary>
    /// <param name="center">The new local center.</param>
    void SetLocalCenter( const glm::vec3& center );

    /// <summary>
    /// Sets this sphere collider's radius.
    /// </summary>
    /// <param name="radius">The new radius.</param>
    void SetRadius( float radius );
};

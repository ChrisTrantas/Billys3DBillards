#pragma once

#include "Collider.hpp"
#include "Math.hpp"
#include <vector>

/// <summary>
/// Defines a box collider.
/// </summary>
class BoxCollider : public Collider
{
    glm::vec3 _center;
    glm::vec3 _size;

public:
    /// <summary>
    /// Creates a new box collider.
    /// </summary>
    /// <param name="gameObject">The game object this component belongs to.</param>
    BoxCollider( GameObject* gameObject );

    /// <summary>
    /// Destroys this box collider.
    /// </summary>
    ~BoxCollider();

    /// <summary>
    /// Gets this box's center in local coordinates.
    /// </summary>
    glm::vec3 GetLocalCenter() const;

    /// <summary>
    /// Gets this box's center in global coordinates.
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
    /// Gets this box collider's size.
    /// </summary>
    glm::vec3 GetSize() const;

    /// <summary>
    /// Queries this box collider for its corner points.
    /// </summary>
    /// <param name="points">The list of points.</param>
    void QueryCorners( std::vector<glm::vec3>& points ) const;

    /// <summary>
    /// Sets this box collider's local center.
    /// </summary>
    /// <param name="center">The new local center.</param>
    void SetLocalCenter( const glm::vec3& center );

    /// <summary>
    /// Sets this box collider's size.
    /// </summary>
    /// <param name="size">The new size.</param>
    void SetSize( const glm::vec3& size );
};

#pragma once

#include "Config.hpp"
#include "BoxCollider.hpp"
#include "RigidBody.h"
#include <array>
#include <memory>
#include <vector>

/// <summary>
/// Defines an octree.
/// </summary>
class Octree
{
    ImplementNonCopyableClass( Octree );
    ImplementNonMovableClass( Octree );

private:
    static std::unordered_map<Collider*, Octree*> _objectOctreeCache;

    const int _subdivision;
    BoxCollider* _bounds;
    std::array<std::shared_ptr<Octree>, 8> _children;
    std::shared_ptr<std::vector<Collider*>> _objects; // Because we won't always have objects

private:
    /// <summary>
    /// Creates a child octree.
    /// </summary>
    Octree( int subdivision, glm::vec3 center, glm::vec3 size );

    /// <summary>
    /// Attmepts to add an object to this octree.
    /// </summary>
    bool AddObject( Collider* object );

    /// <summary>
    /// Attempts to subdivide this octree.
    /// </summary>
    bool Subdivide();

public:
    /// <summary>
    /// Creates a new octree.
    /// </summary>
    Octree();

    /// <summary>
    /// Destroys this octree.
    /// </summary>
    ~Octree();

    /// <summary>
    /// Clears this octree.
    /// </summary>
    void Clear();

    /// <summary>
    /// Gets the number of objects in this octree.
    /// </summary>
    size_t GetObjectCount() const;

    /// <summary>
    /// Checks to see if the given collider is colliding with something.
    /// </summary>
    /// <param name="collider">The collider.</param>
    /// <param name="collidingObject">The collider that the given collider is colliding with.</param>
    bool IsColliding( Collider* collider, Collider** collidingObject );

    /// <summary>
    /// Rebuilds this octree based on the given objects.
    /// </summary>
    /// <param name="objects">The list of objects.</param>
    void Rebuild( std::vector<Collider*>& objects );
};

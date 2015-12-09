#pragma once

#include "Config.hpp"
#include "Math.hpp"
#include <set>
#include <vector>
#include "Collider.hpp"

class Collider;
class BoxCollider;
class SphereCollider;
class RigidBody;

/// <summary>
/// Defines a static class used for physics constants and methods.
/// </summary>
class Physics
{
    ImplementStaticClass( Physics );

    /// <summary>
    /// An enumeration of possible collision types.
    /// </summary>
    enum CollisionType
    {
        Sphere_Sphere,
        Box_Sphere,
        Box_Box
    };

    /// <summary>
    /// Defines a container for collision information.
    /// </summary>
    struct Collision
    {
        Collider* _lhs;
        Collider* _rhs;
        CollisionType _collisionType;

        Collision( Collider* lhs, Collider* rhs, CollisionType collisionType);
    };

private:
    static std::vector<glm::vec3> _lhsCorners;
    static std::vector<glm::vec3> _rhsCorners;
    static std::vector<RigidBody*> _rigidbodies;
    static std::vector<Collision> _collisions;

    /// <summary>
    /// Resolves box <--> sphere collision.
    /// </summary>
    /// <param name="box">The box collider.</param>
    /// <param name="sphere">The sphere collider.</param>
    static void ResolveBoxSphereCollision( BoxCollider* box, SphereCollider* sphere );

    /// <summary>
    /// Resolves sphere <--> sphere collision.
    /// </summary>
    /// <param name="sphere1">The first sphere.</param>
    /// <param name="sphere2">The second sphere.</param>
    static void ResolveSphereSphereCollision( SphereCollider* sphere1, SphereCollider* sphere2 );

    /// <summary>
    /// Resolves the given collision.
    /// </summary>
    /// <param name="collision">The collision to resolve.</param>
    static void ResolveCollision( Collision& collision );

public:
    /// <summary>
    /// Checks for box <--> box collision.
    /// </summary>
    /// <param name="lhs">The first box.</param>
    /// <param name="rhs">The second box.</param>
    static bool AreColliding( BoxCollider* lhs, BoxCollider* rhs );

    /// <summary>
    /// Checks for box <--> sphere collision.
    /// </summary>
    /// <param name="lhs">The box.</param>
    /// <param name="rhs">The sphere.</param>
    static bool AreColliding( BoxCollider* lhs, SphereCollider* rhs );

    /// <summary>
    /// Checks for sphere <--> sphere collision.
    /// </summary>
    /// <param name="lhs">The first sphere.</param>
    /// <param name="rhs">The second sphere.</param>
    static bool AreColliding( SphereCollider* lhs, SphereCollider* rhs );

    /// <summary>
    /// Registers a rigid body to be managed by physics.
    /// </summary>
    /// <param name="rigidBody">The rigid body.</param>
    static void RegisterRigidbody(RigidBody* rigidBody);

    /// <summary>
    /// Un-registers a rigid body to be managed by physics.
    /// </summary>
    /// <param name="rigidBody">The rigid body.</param>
    static void UnregisterRigidbody(RigidBody* rigidBody);

    /// <summary>
    /// Updates the physics system.
    /// </summary>
    static void Update();
};

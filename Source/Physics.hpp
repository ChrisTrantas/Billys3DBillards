#pragma once

#include "Math.hpp"
#include <set>
#include <vector>
#include "Collider.hpp"

class Collider;
class BoxCollider;
class SphereCollider;
class RigidBody;

enum CollisionType
{
	Sphere_Sphere,
	Cube_Sphere,
	Cube_Cube
};

struct Collision
{
	Collider* _lhs;
	Collider* _rhs;
	glm::vec3 _collisionNormal;
	CollisionType collisionType;

	Collision(Collider* lhs, Collider* rhs, glm::vec3 collisionNormal)
	{
		_lhs = lhs;
		_rhs = rhs;
		_collisionNormal = collisionNormal;

		if (_lhs->GetColliderType() == _rhs->GetColliderType())
		{
			if (_lhs->GetColliderType() == ColliderType::Sphere)
			{
				collisionType = CollisionType::Sphere_Sphere;
			}
			else
			{
				collisionType = CollisionType::Cube_Cube;
			}
		}
		else
		{
			collisionType = CollisionType::Cube_Sphere;
		}
	}
};

/// <summary>
/// Defines a static class used for physics constants and methods.
/// </summary>
class Physics
{
    static std::vector<glm::vec3> _lhsCorners;
    static std::vector<glm::vec3> _rhsCorners;
	static std::vector<RigidBody*> _rigidbodies;
	static std::vector<Collision> _collisions;

    // Hide all instance methods
    Physics() = delete;
    Physics( const Physics& ) = delete;
    Physics( Physics&& ) = delete;
    ~Physics() = delete;
    Physics& operator=( const Physics& ) = delete;
    Physics& operator=( Physics&& ) = delete;

public:
    /// <summary>
    /// Checks for box <--> box collision.
    /// </summary>
    /// <param name="lhs">The first box.</param>
    /// <param name="rhs">The second box.</param>
    static bool BoxBoxCollision( const BoxCollider* lhs, const BoxCollider* rhs );

    /// <summary>
    /// Checks for box <--> sphere collision.
    /// </summary>
    /// <param name="lhs">The box.</param>
    /// <param name="rhs">The sphere.</param>
    static bool BoxSphereCollision( const BoxCollider* lhs, const SphereCollider* rhs );

	// Registers a rigidbody with the physics system.
	static void RegisterRigidbody(RigidBody* rigidBody);

    /// <summary>
    /// Checks for sphere <--> sphere collision.
    /// </summary>
    /// <param name="lhs">The first sphere.</param>
    /// <param name="rhs">The second sphere.</param>
    static bool SphereSphereCollision( const SphereCollider* lhs, const SphereCollider* rhs );

	// Unregisters a rigidbody with the physics system.
	static void UnregisterRigidbody(RigidBody* rigidBody);

	// Updates the physics system.
	static void Update();
};

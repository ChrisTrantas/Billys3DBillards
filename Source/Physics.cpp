#include "Physics.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "RigidBody.h"
#include "Time.hpp"
#include "GameObject.hpp"

std::vector<glm::vec3>	Physics::_lhsCorners( 8 );
std::vector<glm::vec3>	Physics::_rhsCorners( 8 );
std::set<RigidBody*>	Physics::_rigidbodies;

// Perform box <--> box collision
bool Physics::BoxBoxCollision( const BoxCollider* lhs, const BoxCollider* rhs )
{
    lhs->QueryCorners( _lhsCorners );
    rhs->QueryCorners( _rhsCorners );

	glm::vec3 lhsHalfWidth = lhs->GetSize() / 2.0f;
	glm::vec3 rhsHalfWidth = lhs->GetSize() / 2.0f;

	CoordinateSystem lhsCoordinateSystem = lhs->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();
	CoordinateSystem rhsCoordinateSystem = rhs->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();

	// Create the rotation and absolute rotation matrices
	glm::mat4 rotation(1.0f);
	glm::mat4 absRotation(1.0f);

	// Compute the rotation and absolute rotation matrices
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			rotation[i][j] = glm::dot(lhsCoordinateSystem[i], rhsCoordinateSystem[j]);
			absRotation[i][j] = abs(rotation[i][j]) + .0001f;
		}
	}

	// Compute the translation vector
	glm::vec3 translation = lhs->GetGlobalCenter() - rhs->GetGlobalCenter();
	translation.x = glm::dot(translation, rhsCoordinateSystem[0]);
	translation.y = glm::dot(translation, rhsCoordinateSystem[1]);
	translation.z = glm::dot(translation, rhsCoordinateSystem[2]);

	float rhsProjectedRadius; // Length of the projection of rhs OBB
	float lhsProjectedRadius; // Length of the projection of lhs OBB

	// Test local axes of this OBB
	for (int i = 0; i < 3; i++)	// Iterates through each dimension of this OBB
	{
		// Sets the projection length of this OBB to the half the length of the box in this OBBs ith dimension
		rhsProjectedRadius = rhsHalfWidth[i];

		// Sets the projection length of that OBB to be its half projection onto this OBBs ith dimension
		lhsProjectedRadius =
			lhsHalfWidth[0] * absRotation[i][0]
			+ lhsHalfWidth[1] * absRotation[i][1]
			+ lhsHalfWidth[2] * absRotation[i][2];

		// Sees if the distance between the the OBB exceed the the combine lengths of the projected Radii
		if (abs(translation[i]) > rhsProjectedRadius + lhsProjectedRadius)
			return false;
	}

	// Test local axes of that OBB
	for (int i = 0; i < 3; i++)	// Iterates through each dimension of this OBB
	{
		// Sets the projection length of this OBB to the half the length of the box in that OBBs ith dimension
		rhsProjectedRadius =
			rhsHalfWidth[0] * absRotation[i][0]
			+ rhsHalfWidth[1] * absRotation[i][1]
			+ rhsHalfWidth[2] * absRotation[i][2];

		// Sets the projection length of that OBB to be its half projection onto that OBBs ith dimension
		lhsProjectedRadius = lhsHalfWidth[i];

		// Sees if the distance between the the OBB exceed the the combine lengths of the projected Radii
		if (abs(translation[i]) > rhsProjectedRadius + lhsProjectedRadius)
			return false;
	}

	// Test axis L = A0 x B0
	rhsProjectedRadius = rhsHalfWidth[1] * absRotation[2][0] + rhsHalfWidth[2] * absRotation[1][0];
	lhsProjectedRadius = lhsHalfWidth[1] * absRotation[0][2] + lhsHalfWidth[2] * absRotation[0][1];
	if (abs(translation[2] * rotation[1][0] - translation[1] * rotation[2][0]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A0 x B1
	rhsProjectedRadius = rhsHalfWidth[1] * absRotation[2][1] + rhsHalfWidth[2] * absRotation[1][1];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[0][2] + lhsHalfWidth[2] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][1] - translation[1] * rotation[2][1]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A0 x B2
	rhsProjectedRadius = rhsHalfWidth[1] * absRotation[2][2] + rhsHalfWidth[2] * absRotation[1][2];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[0][1] + lhsHalfWidth[1] * absRotation[0][0];
	if (abs(translation[2] * rotation[1][2] - translation[1] * rotation[2][2]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A1 x B0
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[2][0] + rhsHalfWidth[2] * absRotation[0][0];
	lhsProjectedRadius = lhsHalfWidth[1] * absRotation[1][2] + lhsHalfWidth[2] * absRotation[1][1];
	if (abs(translation[0] * rotation[2][0] - translation[2] * rotation[0][0]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A1 x B1
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[2][1] + rhsHalfWidth[2] * absRotation[0][1];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[1][2] + lhsHalfWidth[2] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][1] - translation[2] * rotation[0][1]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A1 x B2
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[2][2] + rhsHalfWidth[2] * absRotation[0][2];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[1][1] + lhsHalfWidth[1] * absRotation[1][0];
	if (abs(translation[0] * rotation[2][2] - translation[2] * rotation[0][2]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A2 x B0
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[1][0] + rhsHalfWidth[1] * absRotation[0][0];
	lhsProjectedRadius = lhsHalfWidth[1] * absRotation[2][2] + lhsHalfWidth[2] * absRotation[2][1];
	if (abs(translation[1] * rotation[0][0] - translation[0] * rotation[1][0]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A2 x B1
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[1][1] + rhsHalfWidth[1] * absRotation[0][1];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[2][2] + lhsHalfWidth[2] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][1] - translation[0] * rotation[1][1]) > rhsProjectedRadius + lhsProjectedRadius) return false;

	// Test axis L = A2 x B2
	rhsProjectedRadius = rhsHalfWidth[0] * absRotation[1][2] + rhsHalfWidth[1] * absRotation[0][2];
	lhsProjectedRadius = lhsHalfWidth[0] * absRotation[2][1] + lhsHalfWidth[1] * absRotation[2][0];
	if (abs(translation[1] * rotation[0][2] - translation[0] * rotation[1][2]) > rhsProjectedRadius + lhsProjectedRadius) return false;


    return true;
}

// Perform box <--> sphere collision
bool Physics::BoxSphereCollision( const BoxCollider* lhs, const SphereCollider* rhs )
{
    lhs->QueryCorners( _lhsCorners );

	float sphereRadius = rhs->GetRadius();

	glm::vec3 lhsHalfWidth = lhs->GetSize() / 2.0f;

	CoordinateSystem lhsCoordinateSystem = lhs->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();
	
	// Finds the distances between the centers in the cubes local axis.
	glm::vec3 distance = lhs->GetGlobalCenter() - rhs->GetGlobalCenter();
	distance.x = glm::abs(glm::dot(distance, lhsCoordinateSystem[0]));
	distance.y = glm::abs(glm::dot(distance, lhsCoordinateSystem[1]));
	distance.z = glm::abs(glm::dot(distance, lhsCoordinateSystem[2]));

	// Checks if the distance is greater than the sum of radii
	if (distance.x >= lhsHalfWidth.x + sphereRadius)
		return false;
	if (distance.y >= lhsHalfWidth.y + sphereRadius)
		return false;
	if (distance.z >= lhsHalfWidth.z + sphereRadius)
		return false;

	// Check if the distance is less the boxes radii
	if (distance.x < lhsHalfWidth.x)
		return true;
	if (distance.y < lhsHalfWidth.y)
		return true;
	if (distance.z <lhsHalfWidth.z)
		return true;

	// Checks for corners
	float distanceFromCornor = glm::length(distance - lhsHalfWidth);
    return distanceFromCornor > sphereRadius;
}

// Register a rigid body
void Physics::RegisterRigidbody(RigidBody* rigidBody)
{
    _rigidbodies.insert( rigidBody );
}

// Perform sphere <--> sphere collision
bool Physics::SphereSphereCollision( const SphereCollider* lhs, const SphereCollider* rhs )
{
    float centerDistance = glm::distance(lhs->GetGlobalCenter(), rhs->GetGlobalCenter());
    return centerDistance <= (lhs->GetRadius() + rhs->GetRadius());
}

// Un-register a rigid body
void Physics::UnregisterRigidbody(RigidBody* rigidBody)
{
    if ( _rigidbodies.size() > 0 )
    {
        if ( _rigidbodies.find( rigidBody ) != _rigidbodies.end() )
        {
            _rigidbodies.erase( rigidBody );
        }
    }
}

// Updates the physics system
void Physics::Update()
{
    float time = Time::GetElapsedTime();

    //  Update physics
    // List of collisions with first rigid body
    for (auto& rigidbody : _rigidbodies)
    {
        Collider* thisCollider = rigidbody->GetGameObject()->GetComponentOfType<Collider>();
        if ( thisCollider == nullptr )
        {
            std::cout << rigidbody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
            continue;
        }

        // List of collisions with rest of list 
        for (auto& otherBody : _rigidbodies)
        {
            // No need to check ourselves
            if ( otherBody == rigidbody )
            {
                continue;
            }

			// Check the others
            Collider* otherCollider = otherBody->GetGameObject()->GetComponentOfType<Collider>();
            if ( otherCollider == nullptr )
            {
                std::cout << otherBody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
                continue;
            }

            // Checks if collides
            if (thisCollider->CollidesWith(otherCollider))
            {
				std::cout << thisCollider->GetGameObject()->GetName() << " collided with " << otherCollider->GetGameObject()->GetName() << std::endl;

                // Do collision stuff
                rigidbody->SetVelocity(vec3(0));
                rigidbody->SetAcceleration(-rigidbody->GetAcceleration());

                // Pushes entity back
                otherBody->SetVelocity(vec3(0));
                otherBody->SetAcceleration(-otherBody->GetAcceleration());
            }
        }
        rigidbody->Update();
    }
}

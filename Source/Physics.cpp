#include "Physics.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "RigidBody.h"
#include "Time.hpp"
#include "GameObject.hpp"

std::vector<glm::vec3>	Physics::_lhsCorners( 8 );
std::vector<glm::vec3>	Physics::_rhsCorners( 8 );
std::vector<RigidBody*>	Physics::_rigidbodies;
std::vector<Collision>	Physics::_collisions;

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
	glm::vec3 vectorBetween = lhs->GetGlobalCenter() - rhs->GetGlobalCenter();
	glm::vec3 distance;
	distance.x = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[0]));
	distance.y = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[1]));
	distance.z = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[2]));

	glm::vec3 collisionNormal = glm::normalize(rhs->GetGlobalCenter() - lhs->GetGlobalCenter()) * distance;
	Collision collision = Collision((Collider*)lhs, (Collider*)rhs, collisionNormal);
	// Checks if the distance is greater than the sum of radii
	if (distance.x >= lhsHalfWidth.x + sphereRadius)
		return false;
	if (distance.y >= lhsHalfWidth.y + sphereRadius)
		return false;
	if (distance.z >= lhsHalfWidth.z + sphereRadius)
		return false;

	// Check if the distance is less the boxes radii
	if (distance.x < lhsHalfWidth.x)
	{			
		_collisions.push_back(collision);
		return true;
	}
	if (distance.y < lhsHalfWidth.y)
	{
		_collisions.push_back(collision);
		return true;
	}
	if (distance.z < lhsHalfWidth.z)
	{
		_collisions.push_back(collision);
		return true;
	}

	// Checks for corners
	float distanceFromCornor = glm::length(distance - lhsHalfWidth);

	if (distanceFromCornor < sphereRadius)
	{
		_collisions.push_back(collision);
		return true;
	}
	return false;
}

// Register a rigid body
void Physics::RegisterRigidbody(RigidBody* rigidBody)
{
    _rigidbodies.push_back( rigidBody );
}

// Perform sphere <--> sphere collision
bool Physics::SphereSphereCollision( const SphereCollider* lhs, const SphereCollider* rhs )
{
    float centerDistance = glm::distance(lhs->GetGlobalCenter(), rhs->GetGlobalCenter());


	float sumOfRadii = lhs->GetRadius() + rhs->GetRadius();
	if (centerDistance <= sumOfRadii)
	{
		float magnitude = sumOfRadii - centerDistance;
		glm::vec3 collisionNormal = glm::normalize(rhs->GetGlobalCenter() - lhs->GetGlobalCenter()) * magnitude;

		Collision collision = Collision((Collider*)lhs, (Collider*)rhs, collisionNormal);
		_collisions.push_back(collision);
		return true;
	}
    return false;
}

// Un-register a rigid body
void Physics::UnregisterRigidbody(RigidBody* rigidBody)
{
    if ( _rigidbodies.size() > 0 )
    {

		for (unsigned int i = 0; i < _rigidbodies.size(); i++)
		{
			if (_rigidbodies[i] = rigidBody)
			{
				_rigidbodies.erase(_rigidbodies.begin() + i);
				return;
			}
		}
    }
}

// Updates the physics system
void Physics::Update()
{
    float time = Time::GetElapsedTime();

    //  Update physics
    // List of collisions with first rigid body
	for (unsigned int i = 0; i < _rigidbodies.size(); i++)
    {
		RigidBody* thisRigidBody = _rigidbodies[i];
		Collider* thisCollider = thisRigidBody->GetGameObject()->GetComponentOfType<Collider>();

        if ( thisCollider == nullptr )
        {
			//std::cout << thisRigidBody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
            continue;
        }

        // List of collisions with rest of list 
		for (unsigned int j = i + 1; j < _rigidbodies.size(); j++)
        {
			RigidBody* otherRigidBody = _rigidbodies[j];

			// Check the others
			Collider* otherCollider = otherRigidBody->GetGameObject()->GetComponentOfType<Collider>();
            if ( otherCollider == nullptr )
            {
				std::cout << otherRigidBody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
                continue;
            }

            // Checks if collides
            if (thisCollider->CollidesWith(otherCollider))
            {
				std::cout << thisCollider->GetGameObject()->GetName() << " collided with " << otherCollider->GetGameObject()->GetName() << std::endl;
            }
        }
		thisRigidBody->Update();
    }

	// Goes through list of collisions to resolve
	for (auto& collision : _collisions)
	{
		Collider* thisCollider = collision._lhs;
		RigidBody* thisRigidBody = thisCollider->GetGameObject()->GetComponent<RigidBody>();

		Collider* otherCollider = collision._rhs;
		RigidBody* otherRigidBody = otherCollider->GetGameObject()->GetComponent<RigidBody>();

		if (collision.collisionType == CollisionType::Sphere_Sphere)
		{
			SphereCollider* thisSphere = thisCollider->GetGameObject()->GetComponent<SphereCollider>();
			SphereCollider* otherSphere = otherCollider->GetGameObject()->GetComponent<SphereCollider>();

			// Calculate Penetration
			glm::vec3 betweenCenters = otherSphere->GetGlobalCenter() - thisSphere->GetGlobalCenter();
			float sumOfRadii = otherSphere->GetRadius() + thisSphere->GetRadius();
			float distanceCenters = glm::length(betweenCenters);
			float penetrationDepth = sumOfRadii - distanceCenters;

			// The vector between centers
			betweenCenters = glm::normalize(betweenCenters);

			// Find projected velocities of this sphere
			glm::vec3 v1 = thisRigidBody->GetVelocity();
			float x1 = glm::dot(betweenCenters, v1);
			glm::vec3 v1x = betweenCenters * x1;
			glm::vec3 v1y = v1 - v1x;


			// Find projected velocities of that sphere
			glm::vec3 v2 = otherRigidBody->GetVelocity();
			float x2 = glm::dot(betweenCenters, v2);
			glm::vec3 v2x = betweenCenters * x2;
			glm::vec3 v2y = v2 - v2x;

			// Find masses
			float m1 = thisRigidBody->GetMass();
			float m2 = otherRigidBody->GetMass();

			// Find new velocities
			v1 = v1x * (m1 - m2) / (m1 + m2) + v2x * (2 * m2) / (m1 + m2) + v1y;
			v2 = v1x * (2 * m1) / (m1 + m2) + v2x * (m1 - m2) / (m1 + m2) + v2y;

			// Sets the new velocities
			thisRigidBody->SetVelocity(v1);
			otherRigidBody->SetVelocity(v2);

			thisRigidBody->SetPosition(thisRigidBody->GetPosition() - betweenCenters * penetrationDepth / 2.0f);
			otherRigidBody->SetPosition(otherRigidBody->GetPosition() + betweenCenters * penetrationDepth / 2.0f);
		}
		else if (collision.collisionType == CollisionType::Cube_Sphere)
		{
			SphereCollider* sphereCollider;
			BoxCollider* boxCollider;

			if (thisCollider->GetColliderType() == ColliderType::Sphere)
			{
				sphereCollider = thisCollider->GetGameObject()->GetComponent<SphereCollider>();
				boxCollider = otherCollider->GetGameObject()->GetComponent<BoxCollider>();
			} 
			else
			{
				sphereCollider = otherCollider->GetGameObject()->GetComponent<SphereCollider>();
				boxCollider = thisCollider->GetGameObject()->GetComponent<BoxCollider>();
			}

			RigidBody* sphereRigidBody = sphereCollider->GetGameObject()->GetComponent<RigidBody>();

			// knows who it is colliding with

			// get normal

			// inverse components based on normal

			// determine which inverse to use

			//inverse it

			//CoordinateSystem boxCoordSystem =  boxCollider->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();
			
			glm::vec3 vectorBetween = boxCollider->GetGlobalCenter() - sphereRigidBody->GetPosition();
			
			glm::vec3 boxMin = boxCollider->GetGlobalCenter() - boxCollider->GetSize() * 0.5f;
			glm::vec3 boxMax = boxCollider->GetGlobalCenter() + boxCollider->GetSize() * 0.5f;


			glm::vec3 sphereCenter = sphereCollider->GetGlobalCenter();

			glm::vec3 closestPoint = glm::clamp(sphereCenter, boxMin, boxMax);


			glm::vec3 collisionDistance = closestPoint - sphereCenter;
			float distance = glm::length(collisionDistance);
			float penetration = sphereCollider->GetRadius() - distance;
			glm::vec3 collisionNormal = glm::normalize(collisionDistance);

			sphereRigidBody->SetPosition(sphereCenter - collisionNormal * penetration);

			glm::vec3 newVelocity = glm::reflect(sphereRigidBody->GetVelocity(), collisionNormal);

			sphereRigidBody->SetVelocity(newVelocity);
		}
	}


	_collisions.clear();
}

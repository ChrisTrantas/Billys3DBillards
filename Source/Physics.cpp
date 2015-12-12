#include "Physics.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "RigidBody.h"
#include "Time.hpp"
#include "GameObject.hpp"
#if defined( _DEBUG )
#   include <iostream>
#endif

using namespace glm;

#define MakeCollisionType(a, b) static_cast<Physics::CollisionType>( EnumOR( a, b ) )

std::vector<glm::vec3>  Physics::_lhsCorners( 8 );
std::vector<glm::vec3>  Physics::_rhsCorners( 8 );
std::vector<RigidBody*> Physics::_rigidbodies;
std::vector<Collider*>  Physics::_colliders;
Octree                  Physics::_octree;

// Creates new collision information
Physics::Collision::Collision(Collider* lhs, Collider* rhs, CollisionType collisionType)
    : _lhs( lhs )
    , _rhs( rhs )
    , _collisionType( collisionType)
{
}

// Perform box <--> box collision
bool Physics::AreColliding( BoxCollider* lhs, BoxCollider* rhs )
{
#if 1
    // Gets the half widths of the box colliders.
    glm::vec3 lhsHalfWidth = lhs->GetSize() / 2.0f;
    glm::vec3 rhsHalfWidth = lhs->GetSize() / 2.0f;

    // Gets the local coordinate systems of both the boxes
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

    // Project the translation vector onto the local coordinate systems.
    translation.x = glm::dot(translation, rhsCoordinateSystem[0]);
    translation.y = glm::dot(translation, rhsCoordinateSystem[1]);
    translation.z = glm::dot(translation, rhsCoordinateSystem[2]);

    float rhsProjectedRadius; // Length of the projection of rhs OBB
    float lhsProjectedRadius; // Length of the projection of lhs OBB

    // Test for collisions on the rhs local axis
    for (uint i = 0; i < 3; i++)	// Iterates through each dimension of this OBB
    {
        // Projects rhs on to its local axis
        rhsProjectedRadius = rhsHalfWidth[i];

        // Projects lhs on to rhs's local axis
        lhsProjectedRadius =
            lhsHalfWidth[0] * absRotation[i][0]
            + lhsHalfWidth[1] * absRotation[i][1]
            + lhsHalfWidth[2] * absRotation[i][2];

        // Sees if the distance between the OBB exceed the the combine lengths of the projected Radii
        if (abs(translation[i]) > rhsProjectedRadius + lhsProjectedRadius)
            return false;
    }

    // Test for collisions on the lhs local axis
    for (uint i = 0; i < 3; i++)	// Iterates through each dimension of this OBB
    {
        // Projects lhs on to its local axis
        lhsProjectedRadius = lhsHalfWidth[i];

        // Projects rhs on to lhs's local axis
        rhsProjectedRadius =
            rhsHalfWidth[0] * absRotation[i][0]
            + rhsHalfWidth[1] * absRotation[i][1]
            + rhsHalfWidth[2] * absRotation[i][2];    

        // Sees if the distance between the OBB exceed the the combine lengths of the projected Radii
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
#endif
}

// Perform box <--> sphere collision
bool Physics::AreColliding( BoxCollider* lhs, SphereCollider* rhs )
{
#if 1
    float sphereRadius = rhs->GetRadius();
    glm::vec3 lhsHalfWidth = lhs->GetSize() * 0.5f;

    CoordinateSystem lhsCoordinateSystem = lhs->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();
    
    // The vector from the center of the sphere to the center of the box
    glm::vec3 vectorBetween = lhs->GetGlobalCenter() - rhs->GetGlobalCenter();

    // Does the sphere collision pre-test
    float distBetween2 = glm::dot(vectorBetween, vectorBetween);
    float rad2 = sphereRadius * sphereRadius;
    float halfWidth2 = glm::dot(lhsHalfWidth, lhsHalfWidth);
    if ( distBetween2 > rad2 + halfWidth2 )
    {
        return false;
    }

    // Finds the distances between the centers in the cubes local axis.
    glm::vec3 distance;
    distance.x = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[0]));
    distance.y = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[1]));
    distance.z = glm::abs(glm::dot(vectorBetween, lhsCoordinateSystem[2]));

    // Checks if the distance is greater than the sum of radii for each axis of the box
    if ( ( distance.x >= lhsHalfWidth.x + sphereRadius ) ||
         ( distance.y >= lhsHalfWidth.y + sphereRadius ) ||
         ( distance.z >= lhsHalfWidth.z + sphereRadius ) )
    {
        return false;
    }

    return true;
#endif
}

// Perform sphere <--> sphere collision
bool Physics::AreColliding( SphereCollider* lhs, SphereCollider* rhs )
{
    float centerDistance = glm::distance( lhs->GetGlobalCenter(), rhs->GetGlobalCenter() );
    float sumOfRadii = lhs->GetRadius() + rhs->GetRadius();

    return ( centerDistance <= sumOfRadii );
}

// Gets a collision type between two colliders
Physics::CollisionType Physics::GetCollisionType( Collider* a, Collider* b )
{
    return MakeCollisionType( a->GetColliderType(), b->GetColliderType() );
}

// Register a rigid body
void Physics::RegisterRigidbody(RigidBody* rigidBody)
{
    GameObject* obj = rigidBody->GetGameObject();
    Collider* collider = obj->GetComponentOfType<Collider>();
#if defined( _DEBUG )
    if ( !collider )
    {
        std::cout << "[ERROR] " << obj->GetName() << " does not have a collider yet!!!" << std::endl;
    }
#endif

    _rigidbodies.push_back( rigidBody );
    _colliders.push_back( collider );
}

// Resolves box <--> sphere collision
void Physics::ResolveBoxSphereCollision( BoxCollider* box, SphereCollider* sphere )
{
    // In our game, the boxes are not moved in collisions and are assumed to be oriented.

    //Get The rigid body
    RigidBody* sphereRigidBody = sphere->GetGameObject()->GetComponent<RigidBody>();

    // Find the global centers
    glm::vec3 boxCenter = box->GetGlobalCenter();
    // Finds the center of the sphere in the previous frame
    glm::vec3 sphereCenter = sphere->GetGlobalCenter() - sphereRigidBody->GetVelocity() * Time::GetElapsedTime();
    glm::vec3 betweenCenters = box->GetGlobalCenter() - sphereCenter;

    // Find the range of values inside the box.
    glm::vec3 boxMin = boxCenter - box->GetSize() * 0.5f;
    glm::vec3 boxMax = boxCenter + box->GetSize() * 0.5f;

    // Finds the closest point on the box to the sphere.
    glm::vec3 closestPoint = glm::clamp( sphereCenter, boxMin, boxMax );
    
    // If the sphere's center inside the box, reverse the velocity
    if (closestPoint == sphereCenter)
    {
        sphereRigidBody->SetVelocity(-sphereRigidBody->GetVelocity());
        return;
    }

    // Finds the vector between the closest point and the sphere's center
    glm::vec3 collisionDistance = closestPoint - sphereCenter;

    // Finds the magnitude of penetration based off the length of the collision and the sphere's radius.
    float penetration = sphere->GetRadius() - glm::length(collisionDistance);	

    // Finds the normal vector of the collision.
    glm::vec3 collisionNormal = glm::normalize( collisionDistance );

    // Moves the sphere back until it is no longer penetrating.
    sphereRigidBody->SetPosition( sphereCenter - collisionNormal * penetration);

    // Reflects the sphere's velocity by the collision normal
    glm::vec3 newVelocity = glm::reflect( sphereRigidBody->GetVelocity(), collisionNormal );

    // Sets the new velocity
    sphereRigidBody->SetVelocity( newVelocity );
}

// Resolves sphere <--> sphere collision
void Physics::ResolveSphereSphereCollision( SphereCollider* sphere1, SphereCollider* sphere2 )
{
    // Get the rigid bodies
    RigidBody* sphere1RigidBody = sphere1->GetGameObject()->GetComponent<RigidBody>();
    RigidBody* sphere2RigidBody = sphere2->GetGameObject()->GetComponent<RigidBody>();

    // Calculate Penetration
    glm::vec3 betweenCenters = sphere2->GetGlobalCenter() - sphere1->GetGlobalCenter();
    float sumOfRadii = sphere2->GetRadius() + sphere1->GetRadius();
    float distanceCenters = glm::length( betweenCenters );
    float penetrationDepth = sumOfRadii - distanceCenters + 0.01f;

    // The vector between centers
    betweenCenters = glm::normalize( betweenCenters );

    // To handle collisions, we are finding the momentum of each sphere on the line between centers.
    // We switch the projected momentums between spheres while maintaining the momentum perpendicular to that line.

    // Find projected velocity of sphere one
    glm::vec3 velocity1 = sphere1RigidBody->GetVelocity();
    float x1 = glm::dot(betweenCenters, velocity1);	// The magnitude of the projected velocity.
    glm::vec3 v1proj = betweenCenters * x1;	// The projected velocity
    glm::vec3 v1perp = velocity1 - v1proj;	// The velocity perpendicular to the projected velocity. (It does not matter where it points to)

    // Find projected velocity of sphere two
    glm::vec3 velocity2 = sphere2RigidBody->GetVelocity();
    float x2 = glm::dot(betweenCenters, velocity2);	// The magnitude of the projected velocity.
    glm::vec3 v2proj = betweenCenters * x2; // The projected velocity
    glm::vec3 v2perp = velocity2 - v2proj; // The velocity perpendicular to the projected velocity. (It does not matter where it points to)

    // Find masses
    float mass1 = sphere1RigidBody->GetMass();
    float mass2 = sphere2RigidBody->GetMass();

    float massSum = mass1 + mass2;
    float massDiff = mass1 - mass2;

    // Find new velocities
    velocity1 = v1proj * massDiff / massSum + v2proj * (2 * mass2) / massSum + v1perp;
    velocity2 = v1proj * (2 * mass1) / massSum + v2proj * massDiff / massSum + v2perp;

    // Sets the new velocities
    sphere1RigidBody->SetVelocity(velocity1 * 0.9f);
    sphere2RigidBody->SetVelocity(velocity2 * 0.9f);

    // Moves the spheres so they are no longer colliding
    sphere1RigidBody->SetPosition( sphere1RigidBody->GetPosition() - betweenCenters * penetrationDepth * 0.5f );
    sphere2RigidBody->SetPosition( sphere2RigidBody->GetPosition() + betweenCenters * penetrationDepth * 0.5f );
}

// Resolves the given collision
void Physics::ResolveCollision( Collision& collision )
{
    switch ( collision._collisionType )
    {
        case CollisionType::Sphere_Sphere:
        {
            // Get the two colliders
            SphereCollider* sphere1 = static_cast<SphereCollider*>( collision._lhs );
            SphereCollider* sphere2 = static_cast<SphereCollider*>( collision._rhs );

            ResolveSphereSphereCollision( sphere1, sphere2 );
        }
        break;

        case CollisionType::Box_Sphere:
        {
            SphereCollider* sphere = nullptr;
            BoxCollider*    box = nullptr;

            // Get the sphere and box colliders
            switch ( collision._lhs->GetColliderType() )
            {
                case ColliderType::Sphere:
                {
                    sphere = static_cast<SphereCollider*>( collision._lhs );
                    box = static_cast<BoxCollider*>( collision._rhs );
                }
                break;

                case ColliderType::Box:
                {
                    sphere = static_cast<SphereCollider*>( collision._rhs );
                    box = static_cast<BoxCollider*>( collision._lhs );
                }
                break;
            }

            // Resolve the collision
            ResolveBoxSphereCollision( box, sphere );
        }
        break;
    }
}

// Un-register a rigid body
void Physics::UnregisterRigidbody(RigidBody* rigidBody)
{
    for ( size_t i = 0; i < _rigidbodies.size(); ++i )
    {
        if ( _rigidbodies[ i ] == rigidBody )
        {
            _rigidbodies.erase( _rigidbodies.begin() + i );
            _colliders.erase( _colliders.begin() + i );

            _octree.Rebuild( _colliders );
            break;
        }
    }
}

// Updates the physics system
void Physics::Update()
{
    float time = Time::GetElapsedTime();
    Collision collision( nullptr, nullptr, CollisionType::Sphere_Sphere );


    for (unsigned int i = 0; i < _rigidbodies.size() - 1; i++)
    {
        RigidBody* thisRigidBody = _rigidbodies[i];
        Collider* thisCollider = thisRigidBody->GetGameObject()->GetComponentOfType<Collider>();
        collision._lhs = thisCollider;

        // List of collisions with rest of list 
        for (unsigned int j = i + 1; j < _rigidbodies.size(); j++)
        {
            RigidBody* otherRigidBody = _rigidbodies[j];

            // Check the others
            Collider* otherCollider = otherRigidBody->GetGameObject()->GetComponentOfType<Collider>();
            collision._rhs = otherCollider;

            // Checks if collides
            if ( thisCollider->CollidesWith( otherCollider ) )
            {
                collision._collisionType = GetCollisionType( collision._lhs, collision._rhs );
                ResolveCollision( collision );

                thisCollider->GetGameObject()->GetEventListener()->FireEvent( "OnCollide", otherCollider->GetGameObject() );
                otherCollider->GetGameObject()->GetEventListener()->FireEvent( "OnCollide", thisCollider->GetGameObject() );

                break;
            }
        }
    }

    // Build the octree if this is our first time
    static bool isFirstUpdate = true;
    if ( isFirstUpdate )
    {
        _octree.Rebuild( _colliders );
        isFirstUpdate = false;
    }

    for ( size_t i = 0; i < _colliders.size(); ++i )
    {
        // Get the first collider
        collision._lhs = _colliders[ i ];

        // If we're colliding according to the octree
        if ( _octree.IsColliding( collision._lhs, &( collision._rhs ) ) )
        {
            // Get the collision type
            collision._collisionType = GetCollisionType( collision._lhs, collision._rhs );

            // Resolve the collision
            ResolveCollision( collision );

            // Dispatch the "OnCollide" event
            collision._lhs->GetGameObject()->GetEventListener()->FireEvent( "OnCollide", collision._rhs );
            collision._rhs->GetGameObject()->GetEventListener()->FireEvent( "OnCollide", collision._lhs );

            // Rebuild the octree
            _octree.Rebuild( _colliders );
        }
    }

    // Rebuild the octree
    _octree.Rebuild( _colliders );
}

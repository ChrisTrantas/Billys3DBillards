#include "Physics.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "RigidBody.h"
#include "Time.hpp"
#include "GameObject.hpp"

std::vector<glm::vec3>          Physics::_lhsCorners( 8 );
std::vector<glm::vec3>          Physics::_rhsCorners( 8 );
std::vector<RigidBody*>         Physics::_rigidbodies;
std::vector<Physics::Collision> Physics::_collisions;

// Creates new collision information
Physics::Collision::Collision( Collider* lhs, Collider* rhs, glm::vec3 collisionNormal )
    : _lhs( lhs )
    , _rhs( rhs )
    , _collisionNormal( collisionNormal )
{
    if ( _lhs->GetColliderType() == _rhs->GetColliderType() )
    {
        if ( _lhs->GetColliderType() == ColliderType::Sphere )
        {
            collisionType = CollisionType::Sphere_Sphere;
        }
        else
        {
            collisionType = CollisionType::Box_Box;
        }
    }
    else
    {
        collisionType = CollisionType::Box_Sphere;
    }
}

// Perform box <--> box collision
bool Physics::AreColliding( BoxCollider* lhs, BoxCollider* rhs )
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
bool Physics::AreColliding( BoxCollider* lhs, SphereCollider* rhs )
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
    Collision collision = Collision(lhs, rhs, collisionNormal);
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

// Perform sphere <--> sphere collision
bool Physics::AreColliding( SphereCollider* lhs, SphereCollider* rhs )
{
    float centerDistance = glm::distance( lhs->GetGlobalCenter(), rhs->GetGlobalCenter() );


    float sumOfRadii = lhs->GetRadius() + rhs->GetRadius();
    if ( centerDistance <= sumOfRadii )
    {
        float magnitude = sumOfRadii - centerDistance;
        glm::vec3 collisionNormal = glm::normalize( rhs->GetGlobalCenter() - lhs->GetGlobalCenter() ) * magnitude;

        Collision collision = Collision( lhs, rhs, collisionNormal );
        _collisions.push_back( collision );
        return true;
    }
    return false;
}

// Register a rigid body
void Physics::RegisterRigidbody(RigidBody* rigidBody)
{
    _rigidbodies.push_back( rigidBody );
}

// Resolves box <--> sphere collision
void Physics::ResolveBoxSphereCollision( BoxCollider* box, SphereCollider* sphere )
{
    RigidBody* sphereRigidBody = sphere->GetGameObject()->GetComponent<RigidBody>();

    // knows who it is colliding with

    // get normal

    // inverse components based on normal

    // determine which inverse to use

    //inverse it

    //CoordinateSystem boxCoordSystem =  boxCollider->GetGameObject()->GetTransform()->GetLocalCoordinateSystem();

    glm::vec3 vectorBetween = box->GetGlobalCenter() - sphereRigidBody->GetPosition();

    glm::vec3 boxMin = box->GetGlobalCenter() - box->GetSize() * 0.5f;
    glm::vec3 boxMax = box->GetGlobalCenter() + box->GetSize() * 0.5f;


    glm::vec3 sphereCenter = sphere->GetGlobalCenter();

    glm::vec3 closestPoint = glm::clamp( sphereCenter, boxMin, boxMax );


    glm::vec3 collisionDistance = closestPoint - sphereCenter;
    float distance = glm::length( collisionDistance );
    float penetration = sphere->GetRadius() - distance;
    glm::vec3 collisionNormal = glm::normalize( collisionDistance );

    sphereRigidBody->SetPosition( sphereCenter - collisionNormal * penetration );

    glm::vec3 newVelocity = glm::reflect( sphereRigidBody->GetVelocity(), collisionNormal );

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
    float penetrationDepth = sumOfRadii - distanceCenters;

    // The vector between centers
    betweenCenters = glm::normalize( betweenCenters );

    // Find projected velocities of this sphere
    glm::vec3 v1 = sphere1RigidBody->GetVelocity();
    float x1 = glm::dot( betweenCenters, v1 );
    glm::vec3 v1x = betweenCenters * x1;
    glm::vec3 v1y = v1 - v1x;


    // Find projected velocities of that sphere
    glm::vec3 v2 = sphere2RigidBody->GetVelocity();
    float x2 = glm::dot( betweenCenters, v2 );
    glm::vec3 v2x = betweenCenters * x2;
    glm::vec3 v2y = v2 - v2x;

    // Find masses
    float m1 = sphere1RigidBody->GetMass();
    float m2 = sphere2RigidBody->GetMass();

    // Find new velocities
    v1 = v1x * ( m1 - m2 ) / ( m1 + m2 ) + v2x * ( 2 * m2 ) / ( m1 + m2 ) + v1y;
    v2 = v1x * ( 2 * m1 ) / ( m1 + m2 ) + v2x * ( m1 - m2 ) / ( m1 + m2 ) + v2y;

    // Sets the new velocities
    sphere1RigidBody->SetVelocity( v1 );
    sphere2RigidBody->SetVelocity( v2 );

    sphere1RigidBody->SetPosition( sphere1RigidBody->GetPosition() - betweenCenters * penetrationDepth * 0.5f );
    sphere2RigidBody->SetPosition( sphere2RigidBody->GetPosition() + betweenCenters * penetrationDepth * 0.5f );
}

// Resolves the given collision
void Physics::ResolveCollision( Collision& collision )
{
    if ( collision.collisionType == Physics::Sphere_Sphere )
    {
        // Get the two colliders
        SphereCollider* sphere1 = static_cast<SphereCollider*>( collision._lhs );
        SphereCollider* sphere2 = static_cast<SphereCollider*>( collision._rhs );

        ResolveSphereSphereCollision( sphere1, sphere2 );
    }
    else if ( collision.collisionType == Physics::Box_Sphere )
    {
        SphereCollider* sphere = nullptr;
        BoxCollider*    box = nullptr;

        // Get the sphere and box colliders
        if ( collision._lhs->GetColliderType() == ColliderType::Sphere )
        {
            sphere = static_cast<SphereCollider*>( collision._lhs );
            box    = static_cast<BoxCollider*>   ( collision._rhs );
        }
        else
        {
            sphere = static_cast<SphereCollider*>( collision._rhs );
            box    = static_cast<BoxCollider*>   ( collision._lhs );
        }

        // Resolve the collision
        ResolveBoxSphereCollision( box, sphere );
    }
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
    for (unsigned int i = 0; i < _rigidbodies.size() - 1; i++)
    {
        RigidBody* thisRigidBody = _rigidbodies[i];
        Collider* thisCollider = thisRigidBody->GetGameObject()->GetComponentOfType<Collider>();

        if ( thisCollider == nullptr )
        {
#if defined( _DEBUG )
            std::cout << thisRigidBody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
#endif
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
#if defined( _DEBUG )
                std::cout << otherRigidBody->GetGameObject()->GetName() << " does not have a Collider!" << std::endl;
#endif
                continue;
            }

            // Checks if collides
            if (thisCollider->CollidesWith(otherCollider))
            {
#if defined(_DEBUG)
                std::cout << thisCollider->GetGameObject()->GetName() << " collided with " << otherCollider->GetGameObject()->GetName() << std::endl;
#endif
            }
        }

        // thisRigidBody->Update();
    }

    // Resolve all of the collisions
    for (auto& collision : _collisions)
    {
        ResolveCollision( collision );
    }


    _collisions.clear();
}

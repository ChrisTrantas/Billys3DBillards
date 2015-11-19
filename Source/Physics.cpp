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

    // TODO - This!

    return false;
}

// Perform box <--> sphere collision
bool Physics::BoxSphereCollision( const BoxCollider* lhs, const SphereCollider* rhs )
{
    lhs->QueryCorners( _lhsCorners );

    // TODO - This!

    return false;
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
    // List of collisons with first rigid body
    for (auto& rigidbody : _rigidbodies)
    {
        Collider* thisCollider = rigidbody->GetGameObject()->GetComponentOfType<Collider>();
        if ( thisCollider == nullptr )
        {
            std::cout << rigidbody->GetGameObject()->GetName() << " does not have a RigidBody!" << std::endl;
            continue;
        }

        // List of collisons with rest of list 
        for (auto& otherBody : _rigidbodies)
        {
            // No need to check ourselves
            if ( otherBody == rigidbody )
            {
                continue;
            }

            Collider* otherCollider = otherBody->GetGameObject()->GetComponentOfType<Collider>();
            if ( otherCollider == nullptr )
            {
                std::cout << otherBody->GetGameObject()->GetName() << " does not have a RigidBody!" << std::endl;
                continue;
            }

            // Checks if collides
            if (thisCollider->CollidesWith(otherCollider))
            {
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

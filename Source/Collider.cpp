#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "Physics.hpp"
#include <iostream>

// Creates a new collider
Collider::Collider( GameObject* gameObject, ColliderType type )
    : Component( gameObject )
    , _colliderType( type )
{
}

// Destroys this collider
Collider::~Collider()
{
}

// Gets this collider's type
ColliderType Collider::GetColliderType() const
{
    return _colliderType;
}

// Checks to see if this collider collides with another collider
bool Collider::CollidesWith( const Collider* other )
{
    if ( _colliderType == ColliderType::Box )
    {
        // Get ourselves as a box
        const BoxCollider* thisBox = dynamic_cast<const BoxCollider*>( this );

        // If the other collider is a box, then do box-box collision
        if ( other->GetColliderType() == ColliderType::Box )
        {
            const BoxCollider* thatBox = dynamic_cast<const BoxCollider*>( other );
            return Physics::BoxBoxCollision( thisBox, thatBox );
        }
        // If the other collider is a sphere, then do box-sphere collision
        else if ( other->GetColliderType() == ColliderType::Sphere )
        {
            const SphereCollider* thatSphere = dynamic_cast<const SphereCollider*>( other );
            return Physics::BoxSphereCollision( thisBox, thatSphere );
        }
    }
    else if ( _colliderType == ColliderType::Sphere )
    {
        // Get ourselves as a sphere
        const SphereCollider* thisSphere = dynamic_cast<const SphereCollider*>( this );

        // If the other collider is a box, then do box-sphere collision
        if ( other->GetColliderType() == ColliderType::Box )
        {
            const BoxCollider* thatBox = dynamic_cast<const BoxCollider*>( other );
            return Physics::BoxSphereCollision( thatBox, thisSphere );
        }
        // If the other collider is a sphere, then do sphere-sphere collision
        else if ( other->GetColliderType() == ColliderType::Sphere )
        {
            const SphereCollider* thatSphere = dynamic_cast<const SphereCollider*>( other );
            return Physics::SphereSphereCollision( thisSphere, thatSphere );
        }
    }

#if defined( _DEBUG ) || defined( DEBUG )
    std::cout << "Unknown collider types encountered!" << std::endl;
#endif
    return false;
}

// Updates this collider
void Collider::Update()
{
}

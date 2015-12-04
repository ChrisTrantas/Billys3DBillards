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
bool Collider::CollidesWith( Collider* const other )
{
    if ( _colliderType == ColliderType::Box )
    {
        // Get ourselves as a box
        BoxCollider* thisBox = dynamic_cast<BoxCollider*>( this );

        // If the other collider is a box, then do box-box collision
        if ( other->GetColliderType() == ColliderType::Box )
        {
            BoxCollider* thatBox = dynamic_cast<BoxCollider*>( other );
            return Physics::AreColliding( thisBox, thatBox );
        }
        // If the other collider is a sphere, then do box-sphere collision
        else if ( other->GetColliderType() == ColliderType::Sphere )
        {
            SphereCollider* thatSphere = dynamic_cast<SphereCollider*>( other );
            return Physics::AreColliding( thisBox, thatSphere );
        }
    }
    else if ( _colliderType == ColliderType::Sphere )
    {
        // Get ourselves as a sphere
        SphereCollider* thisSphere = dynamic_cast<SphereCollider*>( this );

        // If the other collider is a box, then do box-sphere collision
        if ( other->GetColliderType() == ColliderType::Box )
        {
            BoxCollider* thatBox = dynamic_cast<BoxCollider*>( other );
            return Physics::AreColliding( thatBox, thisSphere );
        }
        // If the other collider is a sphere, then do sphere-sphere collision
        else if ( other->GetColliderType() == ColliderType::Sphere )
        {
            SphereCollider* thatSphere = dynamic_cast<SphereCollider*>( other );
            return Physics::AreColliding( thisSphere, thatSphere );
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

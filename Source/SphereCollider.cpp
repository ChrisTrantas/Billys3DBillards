#include "SphereCollider.hpp"
#include "GameObject.hpp"

// Creates a new sphere collider
SphereCollider::SphereCollider( GameObject* gameObject )
    : Collider( gameObject, ColliderType::Sphere )
    , _center( 0, 0, 0 )
    , _radius( 0 )
{
}

// Destroys this sphere collider.
SphereCollider::~SphereCollider()
{
    _radius = 0;
}

// Gets this sphere's center in local coordinates
glm::vec3 SphereCollider::GetLocalCenter() const
{
    return _center;
}

// Gets this sphere's center in global coordinates
glm::vec3 SphereCollider::GetGlobalCenter() const
{
    return TransformVector( _gameObject->GetWorldMatrix(), _center );
}

// Gets this sphere's radius
float SphereCollider::GetRadius() const
{
    return _radius;
}

// Sets this sphere collider's local center
void SphereCollider::SetLocalCenter( const glm::vec3& center )
{
    _center = center;
}

// Sets this sphere collider's radius
void SphereCollider::SetRadius( float radius )
{
    _radius = glm::abs( radius );
}

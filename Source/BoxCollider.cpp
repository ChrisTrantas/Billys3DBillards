#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

// Creates a new box collider
BoxCollider::BoxCollider( GameObject* gameObject )
    : Collider( gameObject, ColliderType::Box )
    , _center( 0, 0, 0 )
    , _size( 0, 0, 0 )
{
}

// Destroys this box collider
BoxCollider::~BoxCollider()
{
}

// Gets this box collider's local center
glm::vec3 BoxCollider::GetLocalCenter() const
{
    return _center;
}

// Gets this box collider's global center
glm::vec3 BoxCollider::GetGlobalCenter() const
{
    return TransformVector( _gameObject->GetWorldMatrix(), _center );
}

// Gets this box collider's size
glm::vec3 BoxCollider::GetSize() const
{
	glm::vec3 scale = _gameObject->GetTransform()->GetScale();
    return _size * scale;
}

// Queries this box collider's corners
void BoxCollider::QueryCorners( std::vector<glm::vec3>& points ) const
{
    points.clear();

    if ( points.size() != 8 )
    {
        points.resize( 8 );
    }

    glm::vec3 hSize = _size * 0.5f;
    points[ 0 ] = glm::vec3( _center.x - hSize.x, _center.y - hSize.y, _center.z - hSize.z );
    points[ 1 ] = glm::vec3( _center.x - hSize.x, _center.y - hSize.y, _center.z + hSize.z );
    points[ 2 ] = glm::vec3( _center.x - hSize.x, _center.y + hSize.y, _center.z - hSize.z );
    points[ 3 ] = glm::vec3( _center.x - hSize.x, _center.y + hSize.y, _center.z + hSize.z );
    points[ 4 ] = glm::vec3( _center.x + hSize.x, _center.y - hSize.y, _center.z - hSize.z );
    points[ 5 ] = glm::vec3( _center.x + hSize.x, _center.y - hSize.y, _center.z + hSize.z );
    points[ 6 ] = glm::vec3( _center.x + hSize.x, _center.y + hSize.y, _center.z - hSize.z );
    points[ 7 ] = glm::vec3( _center.x + hSize.x, _center.y + hSize.y, _center.z + hSize.z );

    glm::mat4 world = _gameObject->GetWorldMatrix();
    for ( size_t i = 0; i < 8; ++i )
    {
        points[ i ] = TransformVector( world, points[ i ] );
    }
}

// Sets this box collider's local center
void BoxCollider::SetLocalCenter( const glm::vec3& center )
{
    _center = center;
}

// Sets this box collider's size
void BoxCollider::SetSize( const glm::vec3& size )
{
    _size = glm::abs( size );
}

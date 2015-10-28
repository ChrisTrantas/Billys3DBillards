#include "Transform.hpp"

// Constructor
Transform::Transform( GameObject* gameObj )
    : Component( gameObj )
    , _world( 1.0f )
    , _position( 0, 0, 0 )
    , _rotation( 0, 0, 0 )
    , _scale( 1, 1, 1 )
    , _isWorldDirty( false )
{
}

// Destructor
Transform::~Transform()
{
}

// Get the position
glm::vec3 Transform::GetPosition() const
{
    return _position;
}

// Get the scale
glm::vec3 Transform::GetScale() const
{
    return _scale;
}

// Get the rotation
glm::vec3 Transform::GetRotation() const
{
    return _rotation;
}

// Gets the world matrix
glm::mat4 Transform::GetWorldMatrix()
{
    if ( _isWorldDirty )
    {
        // Calculate the rotation matrix
        // TODO - Use a quaternion?
        glm::mat4 rotationMatrix = glm::rotate( _rotation.x, glm::vec3( 1, 0, 0 ) )
                                 * glm::rotate( _rotation.y, glm::vec3( 0, 1, 0 ) )
                                 * glm::rotate( _rotation.z, glm::vec3( 0, 0, 1 ) );

        // Now multiply to get our world matrix
        _world  = glm::mat4( 1.0f );
        _world *= glm::translate( _position )
               *  rotationMatrix
               *  glm::scale( _scale );

        // Update our flag to show that we don't need to be updated
        _isWorldDirty = false;
    }

    return _world;
}

// Set the position
void Transform::SetPosition( glm::vec3 nPos )
{
    _position = nPos;
    _isWorldDirty = true;
}

// Set the scale
void Transform::SetScale( glm::vec3 nSca )
{
    _scale = nSca;
    _isWorldDirty = true;
}

// Set the roattion
void Transform::SetRotation( glm::vec3 nRot )
{
    _rotation = nRot;
    _isWorldDirty = true;
}

// Updates this transform
void Transform::Update()
{
}

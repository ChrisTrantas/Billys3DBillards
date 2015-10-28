#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

/// <summary>
/// Defines a transform.
/// </summary>
class Transform : public Component
{
    friend class TweenRotation;
    friend class TweenPosition;
    friend class TweenScale;

protected:
    glm::mat4 _world;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
    bool _isWorldDirty;

public:
    /// <summary>
    /// Creates a new transform.
    /// </summary>
    /// <param name="gameObj">The parent GameObject of this transform.</param>
    Transform( GameObject* gameObj );

    /// <summary>
    /// Destroys this transform.
    /// </summary>
    ~Transform();

    /// <summary>
    /// Returns the position of this transform.
    /// </summary>
    glm::vec3 GetPosition() const;

    /// <summary>
    /// Returns the scale of this transform.
    /// </summary>
    glm::vec3 GetScale() const;

    /// <summary>
    /// Returns the rotation of this transform in Euler angles.
    /// </summary>
    glm::vec3 GetRotation() const;

    /// <summary>
    /// Gets the world matrix of this transform.
    /// </summary>
    glm::mat4 GetWorldMatrix();

    /// <summary>
    /// Sets this transform to the given position.
    /// </summary>
    /// <param name="nPos">The position to move this transform to.</param>
    void SetPosition( glm::vec3 nPos );

    /// <summary>
    /// Sets this transform to a given scale.
    /// </summary>
    /// <param name="nSca">The scale to set this transform to.</param>
    void SetScale( glm::vec3 nSca );

    /// <summary>
    /// Sets this transform to a given rotation in Euler angles.
    /// </summary>
    /// <param name="">The rotation to set this transform to.</param>
    void SetRotation( glm::vec3 nRot );

    /// <summary>
    /// Updates this component.
    /// </summary>
    void Update() override;
};


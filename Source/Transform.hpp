#pragma once

#include "Component.hpp"
#include "GameObject.hpp"

/// <summary>
/// Defines a coordinate system
/// </summary>
struct CoordinateSystem
{
	// The axis of the coordinate system
	glm::vec3 XAxis;
	glm::vec3 YAxis;
	glm::vec3 ZAxis;

	/// <summary>
	/// Gets one of the axis
	/// </summary>
	inline glm::vec3 operator[](size_t index) const
	{
		glm::vec3 result;
		switch (index)
		{
		case 0: result = XAxis; break;
		case 1: result = YAxis; break;
		case 2: result = ZAxis; break;
		}
		return result;
	}
};

/// <summary>
/// Defines a transform.
/// </summary>
class Transform : public Component
{
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
	/// Gets an array of unit vectors the represent the local coordinate system of the game object
	/// </summary>
	CoordinateSystem GetLocalCoordinateSystem() const;

    /// <summary>
    /// Updates this component.
    /// </summary>
    void Update() override;
};


#pragma once

#include "Mesh.hpp"
#include "Math.hpp"
#include "Components.hpp"
#include <string>
#include <unordered_map>
#include <vector>


class RigidBody : public Component
{
	
	glm::vec3 m_v3Position;
	glm::vec3 m_v3Velocity;
	glm::vec3 m_v3Acceleration;
	Transform* transform;

	glm::quat m_qOrientation;

	float m_fMass;
	float m_fMaxAcc;
	const float m_fBallFriction = 0.1f;
	//const float m_CushionFriction = 0.2f;

	bool _AtRest; // Is true when the object has no velocity
	bool _IsMovable;	// Is true when the object can move

public:

	RigidBody( GameObject* gameObject );

	~RigidBody();

	void Update(void);

	void SetMaxAcc(float a_fMaxAcc);
	void SetMass(float a_fMass);
	float GetMass();
	void SetPosition(glm::vec3 a_v3Position);
	vec3 GetPosition();
	void SetVelocity(glm::vec3 a_v3Velocity);
	vec3 GetVelocity();
	void SetAcceleration(glm::vec3 a_v3Acceleration);
	vec3 GetAcceleration();
	void AddForce(const glm::vec3& force);
	vec3 GetForce();

	bool IsAtRest();
	bool IsMovable();
	void SetIsMovable(bool isMovable);
};


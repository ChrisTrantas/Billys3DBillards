#include "RigidBody.h"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

RigidBody::RigidBody(GameObject* gameObject)
	: Component(gameObject)
{
	Physics::RegisterRigidbody(this);
}

RigidBody::~RigidBody()
{
	Physics::UnregisterRigidbody(this);
}

void RigidBody::SetPosition(glm::vec3 a_v3Position)
{
	m_v3Position = a_v3Position;
}

vec3 RigidBody::GetPosition(){ return m_v3Position; }

void RigidBody::SetVelocity(glm::vec3 a_v3Velocity)
{
	m_v3Velocity = a_v3Velocity;
}

vec3 RigidBody::GetVelocity(){ return m_v3Velocity; }

void RigidBody::SetAcceleration(glm::vec3 a_v3Acceleration)
{
	m_v3Acceleration = a_v3Acceleration;
}

vec3 RigidBody::GetAcceleration(){ return m_v3Acceleration; }

void RigidBody::SetMaxAcc(float a_fMaxAcc)
{
	m_fMaxAcc = a_fMaxAcc;
}

void RigidBody::SetMass(float a_fMass)
{
	m_fMass = abs( a_fMass );
}

float RigidBody::GetMass(){ return m_fMass; }

void RigidBody::AddForce(const glm::vec3& force)
{
	// Calculate acceleration based off of applied force and mass
	float invMass = (m_fMass == 0.0f) ? 0.0f : (1.0f / m_fMass);
	m_v3Acceleration += force * invMass;
	m_v3Acceleration = glm::clamp(m_v3Acceleration, -m_fMaxAcc, m_fMaxAcc);
}


void RigidBody::Update(void)
{
	// Apply Friction
	AddForce(-m_v3Acceleration * m_fBallFriction);

	m_v3Velocity = m_v3Velocity + (m_v3Acceleration);

	m_v3Position = m_v3Position + m_v3Velocity;

	Transform* transformPointer = _gameObject->GetTransform();
	transformPointer->SetPosition(m_v3Position);
	
}

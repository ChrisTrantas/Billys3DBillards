#include "RigidBody.h"

void RigidBody::Init(void)
{
	m_v3Position = glm::vec3();
	m_qOrientation = glm::quat();
	m_v3Scale = glm::vec3();

	m_v3Velocity = glm::vec3();
	m_v3Acceleration = glm::vec3();

	m_fMass = 1.0f;
	m_fMaxAcc = 10.0f;
}

void RigidBody::Swap(RigidBody& other)
{
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_qOrientation, other.m_qOrientation);
	std::swap(m_v3Scale, other.m_v3Scale);

	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Acceleration, other.m_v3Acceleration);

	std::swap(m_fMaxAcc, other.m_fMaxAcc);
}

void RigidBody::Release(void)
{
}

RigidBody::RigidBody()
{
}

RigidBody::RigidBody(RigidBody const& other)
{
	m_v3Position = other.m_v3Position;
	m_qOrientation = other.m_qOrientation;
	m_v3Scale = other.m_v3Scale;

	m_v3Velocity = other.m_v3Velocity;
	m_v3Acceleration = other.m_v3Acceleration;

	m_fMaxAcc = other.m_fMaxAcc;
}

RigidBody& RigidBody::operator=(RigidBody const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		RigidBody temp(other);
		Swap(temp);
	}
	return *this;
}

RigidBody::~RigidBody()
{
}

void RigidBody::SetPosition(glm::vec3 a_v3Position)
{
	m_v3Position = a_v3Position;
}

void RigidBody::SetVelocity(glm::vec3 a_v3Velocity)
{
	m_v3Velocity = a_v3Velocity;
}
void RigidBody::SetAcceleration(glm::vec3 a_v3Acceleration)
{
	m_v3Acceleration = a_v3Acceleration;
}
void RigidBody::SetMaxAcc(float a_fMaxAcc)
{
	m_fMaxAcc = a_fMaxAcc;
}
void RigidBody::SetMass(float a_fMass)
{
	m_fMass = a_fMass;
}

void RigidBody::AddForce(const glm::vec3& force)
{
	float invMass = (m_fMass == 0.0f) ? 0.0f : (1.0f / m_fMass);
	m_v3Acceleration += force * invMass;

	m_v3Velocity = m_v3Velocity + (m_v3Acceleration);
	m_v3Position = m_v3Position + m_v3Velocity;

	glm::mat4 m4ToWorld = glm::translate(m_v3Position);

}

void RigidBody::Update(void)
{
	//glm::vec3 v3Acceleration = m_v3Acceleration * 1.0f / m_fMass;
	//v3Acceleration = glm::clamp(v3Acceleration, -m_fMaxAcc, m_fMaxAcc);
	//
	//m_v3Velocity = m_v3Velocity + (v3Acceleration);
	//m_v3Position = m_v3Position + m_v3Velocity;
	//
	//glm::mat4 m4ToWorld = glm::translate(m_v3Position);
}
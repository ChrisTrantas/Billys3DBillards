#include "RigidBody.h"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

#define MIN_SPEED 0.1f

RigidBody::RigidBody(GameObject* gameObject)
    : Component(gameObject)
    , m_fBallFriction( 0.625f )
    , m_fMass( 1.0f )
    , m_fMaxAcc( 100.0f )
    , m_v3Position( 0, 0, 0 )
    , m_v3Velocity( 0, 0, 0 )
{
    Physics::RegisterRigidbody(this);
    transform = gameObject->GetTransform();
    m_v3Position = transform->GetPosition();
}

RigidBody::~RigidBody()
{
    Physics::UnregisterRigidbody(this);
}

void RigidBody::SetPosition(glm::vec3 a_v3Position)
{
    m_v3Position = a_v3Position;
    transform->SetPosition(m_v3Position);
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
   /// m_v3Acceleration = glm::clamp(m_v3Acceleration, -m_fMaxAcc, m_fMaxAcc);
}

void RigidBody::Update(void)
{
    // Apply Friction
    AddForce(-m_v3Velocity * m_fBallFriction);

    m_v3Velocity = m_v3Velocity + (m_v3Acceleration * Time::GetElapsedTime()); 
    m_v3Acceleration = glm::vec3(0);

    //m_v3Position = m_v3Position + m_v3Velocity;
    m_v3Position = transform->GetPosition();
    m_v3Position += m_v3Velocity * Time::GetElapsedTime();
    transform->SetPosition(m_v3Position);
    
    if ( glm::abs( m_v3Velocity.x ) < MIN_SPEED ) m_v3Velocity.x = 0;
    if ( glm::abs( m_v3Velocity.y ) < MIN_SPEED ) m_v3Velocity.y = 0;
    if ( glm::abs( m_v3Velocity.z ) < MIN_SPEED ) m_v3Velocity.z = 0;

    _AtRest = ( 0 == glm::dot( m_v3Velocity, m_v3Velocity ) );
}

bool RigidBody::IsAtRest()
{
    return _AtRest;
}

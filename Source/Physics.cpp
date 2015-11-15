#include "Physics.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"

std::vector<glm::vec3> Physics::_lhsCorners( 8 );
std::vector<glm::vec3> Physics::_rhsCorners( 8 );

// Perform box <--> box collision
bool Physics::BoxBoxCollision( const BoxCollider* lhs, const BoxCollider* rhs )
{
    lhs->QueryCorners( _lhsCorners );
    rhs->QueryCorners( _rhsCorners );

    // TODO - This!

    return false;
}

// Perform box <--> sphere collision
bool Physics::BoxSphereCollision( const BoxCollider* lhs, const SphereCollider* rhs )
{
    lhs->QueryCorners( _lhsCorners );

    // TODO - This!

    return false;
}

// Perform sphere <--> sphere collision
bool Physics::SphereSphereCollision( const SphereCollider* lhs, const SphereCollider* rhs )
{

    // TODO - This!

    return false;
}

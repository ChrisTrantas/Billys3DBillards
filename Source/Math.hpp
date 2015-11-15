#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/// <summary>
/// Transforms a vec3 by a mat4.
/// </summary>
/// <param name="matrix">The matrix.</param>
/// <param name="vector">The vector.</param>
inline glm::vec3 TransformVector( const glm::mat4& matrix, const glm::vec3& vector )
{
    return glm::vec3( matrix * glm::vec4( vector, 1.0f ) );
}

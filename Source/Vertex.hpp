#pragma once

#include "Math.hpp"

/// <summary>
/// Defines a vertex.
/// </summary>
struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec2 UV;
};

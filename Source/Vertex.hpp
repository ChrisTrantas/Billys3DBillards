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

/// <summary>
/// Defines a vertex used when rendering text.
/// </summary>
struct TextVertex
{
    glm::vec2 Position;
    glm::vec2 UV;

    TextVertex()
        : TextVertex( 0, 0, 0, 0 )
    {
    }

    TextVertex( float x, float y, float u, float v )
        : Position( x, y )
        , UV( u, v )
    {
    }
};

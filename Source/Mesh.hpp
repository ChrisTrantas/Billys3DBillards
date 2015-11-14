#pragma once

#include <vector>
#include "Material.hpp"
#include "Vertex.hpp"

/// <summary>
/// Defines a mesh.
/// </summary>
class Mesh
{
    struct MeshData
    {
        unsigned int VBO;
        unsigned int VAO;
        unsigned int IndexCount;

        MeshData();
    };

    MeshData _data;
    
    // Prevent use of the move constructor and assignment operator
    Mesh( Mesh&& ) = delete;
    Mesh& operator=( Mesh&& ) = delete;

public:
    /// <summary>
    /// Creates a new mesh.
    /// </summary>
    /// <param name="vertices">The vertices to use.</param>
    /// <param name="indices">The indices to use.</param>
    Mesh( const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices );

    /// <summary>
    /// Destroys this mesh.
    /// </summary>
    ~Mesh();

    /// <summary>
    /// Draws this mesh.
    /// </summary>
    /// <param name="material">The material to use to draw.</param>
    void Draw( const Material* material );
};

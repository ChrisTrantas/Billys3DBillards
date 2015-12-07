#pragma once

#include <functional>
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
        unsigned int IBO;
        unsigned int VertexCount;
        unsigned int VertexStride;
        unsigned int IndexCount;

        MeshData();
    };

    MeshData _data;
    std::function<void( const MeshData&, Material* const )> _drawCallback;
    
    // Prevent use of the move constructor and assignment operator
    Mesh( Mesh&& ) = delete;
    Mesh& operator=( Mesh&& ) = delete;

    /// <summary>
    /// Creates this mesh's buffers.
    /// </summary>
    /// <param name="vertices">The vertices to use.</param>
    /// <param name="indices">The indices to use.</param>
    template<typename TVertex> void CreateBuffers( const std::vector<TVertex>& vertices, const std::vector<unsigned>& indices );

    /// <summary>
    /// Creates this mesh's draw callback.
    /// </summary>
    template<typename TVertex> void CreateDrawCallback();

public:
    /// <summary>
    /// Creates a new mesh.
    /// </summary>
    /// <param name="vertices">The vertices to use.</param>
    /// <param name="indices">The indices to use.</param>
    template<typename TVertex> Mesh( const std::vector<TVertex>& vertices, const std::vector<unsigned>& indices );

    /// <summary>
    /// Destroys this mesh.
    /// </summary>
    ~Mesh();

    /// <summary>
    /// Draws this mesh.
    /// </summary>
    /// <param name="material">The material to use to draw.</param>
    void Draw( Material* const material );
};

#include "Mesh.inl"

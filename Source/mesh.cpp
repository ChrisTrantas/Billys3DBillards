#include "Mesh.hpp"

typedef unsigned int UINT;

// Create new mesh data
Mesh::MeshData::MeshData()
    : VAO( 0 )
    , VBO( 0 )
    , IndexCount( 0 )
{
}

// Create a new mesh
Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<UINT>& indices )
{
}

// Destroy this mesh
Mesh::~Mesh()
{
}

// Draw this mesh
void Mesh::Draw( const Material* material )
{
    // TODO - This!
}

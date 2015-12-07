#include "Mesh.hpp"

// Create new mesh data
Mesh::MeshData::MeshData()
    : VBO( 0 )
    , IBO( 0 )
    , IndexCount( 0 )
    , VertexCount( 0 )
    , VertexStride( 0 )
{
}

// Destroy this mesh
Mesh::~Mesh()
{
}

// Draw this mesh
void Mesh::Draw( Material* const material )
{
    glUseProgram( material->GetProgramID() );
    material->SendValuesToShader();

    // Bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, _data.VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _data.IBO );


    _drawCallback( _data, material );


    // Un-bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

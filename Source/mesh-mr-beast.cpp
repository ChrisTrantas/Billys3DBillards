#include "Mesh.hpp"

typedef unsigned int UINT;

#define glOffset(Type, Count) reinterpret_cast<void*>( sizeof( Type ) * Count )

// Create new mesh data
Mesh::MeshData::MeshData()
    : VBO( 0 )
    , IBO( 0 )
    , IndexCount( 0 )
    , VertexCount( 0 )
{
}

// Create a new mesh
Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<UINT>& indices )
{
    // Copy the buffer data over
    glGenBuffers( 1, &_data.VBO );
    glBindBuffer( GL_ARRAY_BUFFER, _data.VBO );
    glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[ 0 ], GL_STATIC_DRAW );
    _data.VertexCount = vertices.size();
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // Copy the index data over
    glGenBuffers( 1, &_data.IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _data.IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( UINT ), &indices[ 0 ], GL_STATIC_DRAW );
    _data.IndexCount = indices.size();
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

// Destroy this mesh
Mesh::~Mesh()
{
}

// Draw this mesh
void Mesh::Draw( const Material* material )
{
    // Get the attribute locations
    GLint attrVertex  = material->GetAttributeLocation( "Vertex" );
    GLint attrNormal  = material->GetAttributeLocation( "Normal" );
    GLint attrTangent = material->GetAttributeLocation( "Tangent" );
    GLint attrUV      = material->GetAttributeLocation( "UV" );

    // Bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, _data.VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _data.IBO );



    // Enable the attributes
    glEnableVertexAttribArray( attrVertex );
    glEnableVertexAttribArray( attrNormal );
    glEnableVertexAttribArray( attrTangent );
    glEnableVertexAttribArray( attrUV );
    glVertexAttribPointer( attrVertex,  3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 0 ) );
    glVertexAttribPointer( attrNormal,  3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 1 ) );
    glVertexAttribPointer( attrTangent, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 2 ) );
    glVertexAttribPointer( attrUV,      2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 3 ) );



    // Draw the buffer!
    glDrawElements( GL_TRIANGLES, _data.IndexCount, GL_UNSIGNED_INT, nullptr );
    


    // Disable the attributes
    glDisableVertexAttribArray( attrVertex );
    glDisableVertexAttribArray( attrNormal );
    glDisableVertexAttribArray( attrTangent );
    glDisableVertexAttribArray( attrUV );

    // Un-bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

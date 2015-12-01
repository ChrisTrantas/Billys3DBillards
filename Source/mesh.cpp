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
void Mesh::Draw( Material* const material )
{
    glUseProgram(material->GetProgramID());
	material->SendValuesToShader();

    // Get the attribute locations
    GLint attrVertex  = material->GetAttributeLocation( "vertPosition" );
    GLint attrNormal  = material->GetAttributeLocation( "vertNormal" );
    GLint attrTangent = material->GetAttributeLocation( "vertTangent" );
    GLint attrUV      = material->GetAttributeLocation( "vertUV" );

    // Bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, _data.VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _data.IBO );



    // Enable the attributes
    if ( attrVertex >= 0 )
    {
        glEnableVertexAttribArray( attrVertex );
        glVertexAttribPointer( attrVertex, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 0 ) );
    }
    if ( attrNormal >= 0 )
    {
        glEnableVertexAttribArray( attrNormal );
        glVertexAttribPointer( attrNormal, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 1 ) );
    }
    if ( attrTangent >= 0 )
    {
        glEnableVertexAttribArray( attrTangent );
        glVertexAttribPointer( attrTangent, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 2 ) );
    }
    if ( attrUV >= 0 )
    {
        glEnableVertexAttribArray( attrUV );
        glVertexAttribPointer( attrUV, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), glOffset( glm::vec3, 3 ) );
    }



    // Draw the buffer!
    glDrawElements( GL_TRIANGLES, _data.IndexCount, GL_UNSIGNED_INT, nullptr );
    


    // Disable the attributes
    if ( attrVertex  >= 0 ) glDisableVertexAttribArray( attrVertex );
    if ( attrNormal  >= 0 ) glDisableVertexAttribArray( attrNormal );
    if ( attrTangent >= 0 ) glDisableVertexAttribArray( attrTangent );
    if ( attrUV      >= 0 ) glDisableVertexAttribArray( attrUV );

    // Un-bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

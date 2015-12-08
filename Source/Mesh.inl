#pragma once

#define glOffset(Type, Count) reinterpret_cast<void*>( sizeof( Type ) * Count )

// Creates a new mesh
template<typename TVertex> Mesh::Mesh( const std::vector<TVertex>& vertices, const std::vector<unsigned>& indices )
{
    CreateBuffers<TVertex>( vertices, indices );
    CreateDrawCallback<TVertex>();
}

// Creates this mesh's buffers
template<typename TVertex> void Mesh::CreateBuffers( const std::vector<TVertex>& vertices, const std::vector<unsigned>& indices )
{
    typedef unsigned int UINT;

    // Copy the buffer data over
    if ( vertices.size() )
    {
        glGenBuffers( 1, &_data.VBO );
        glBindBuffer( GL_ARRAY_BUFFER, _data.VBO );
        glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( TVertex ), &vertices[ 0 ], GL_STATIC_DRAW );
        _data.VertexCount = vertices.size();
        _data.VertexStride = sizeof( TVertex );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }

    // Copy the index data over
    if ( indices.size() )
    {
        glGenBuffers( 1, &_data.IBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _data.IBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( UINT ), &indices[ 0 ], GL_STATIC_DRAW );
        _data.IndexCount = indices.size();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
}

// Failure to create a draw callback
template<typename TVertex> inline void Mesh::CreateDrawCallback()
{
    throw std::exception( "Cannot create draw callback for unknown vertex type" );
}

// Specialized draw callback for mesh vertices
template<> inline void Mesh::CreateDrawCallback<Vertex>()
{
    _drawCallback = []( const MeshData& data, Material* const material )
    {
        // Get the attribute locations
        GLint attrVertex = material->GetAttributeLocation( "vertPosition" );
        GLint attrNormal = material->GetAttributeLocation( "vertNormal" );
        GLint attrTangent = material->GetAttributeLocation( "vertTangent" );
        GLint attrUV = material->GetAttributeLocation( "vertUV" );


        // Enable the attributes
        if ( attrVertex >= 0 )
        {
            glEnableVertexAttribArray( attrVertex );
            glVertexAttribPointer( attrVertex, 3, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec3, 0 ) );
        }
        if ( attrNormal >= 0 )
        {
            glEnableVertexAttribArray( attrNormal );
            glVertexAttribPointer( attrNormal, 3, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec3, 1 ) );
        }
        if ( attrTangent >= 0 )
        {
            glEnableVertexAttribArray( attrTangent );
            glVertexAttribPointer( attrTangent, 3, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec3, 2 ) );
        }
        if ( attrUV >= 0 )
        {
            glEnableVertexAttribArray( attrUV );
            glVertexAttribPointer( attrUV, 2, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec3, 3 ) );
        }


        // Draw the buffer!
        glDrawElements( GL_TRIANGLES, data.IndexCount, GL_UNSIGNED_INT, nullptr );


        // Disable the attributes
        if ( attrVertex >= 0 ) glDisableVertexAttribArray( attrVertex );
        if ( attrNormal >= 0 ) glDisableVertexAttribArray( attrNormal );
        if ( attrTangent >= 0 ) glDisableVertexAttribArray( attrTangent );
        if ( attrUV >= 0 ) glDisableVertexAttribArray( attrUV );
    };
}

// Specialized draw callback for text vertices
template<> inline void Mesh::CreateDrawCallback<TextVertex>()
{
    _drawCallback = []( const MeshData& data, Material* const material )
    {
        // Get the attribute locations
        GLint attrVertex = material->GetAttributeLocation( "vertPosition" );
        GLint attrUV = material->GetAttributeLocation( "vertUV" );


        // Enable the attributes
        if ( attrVertex >= 0 )
        {
            glEnableVertexAttribArray( attrVertex );
            glVertexAttribPointer( attrVertex, 3, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec2, 0 ) );
        }
        if ( attrUV >= 0 )
        {
            glEnableVertexAttribArray( attrUV );
            glVertexAttribPointer( attrUV, 2, GL_FLOAT, GL_FALSE, data.VertexStride, glOffset( glm::vec2, 1 ) );
        }


        // Draw the buffer!
        glDrawArrays( GL_TRIANGLES, 0, data.VertexCount );


        // Disable the attributes
        if ( attrVertex >= 0 ) glDisableVertexAttribArray( attrVertex );
        if ( attrUV >= 0 ) glDisableVertexAttribArray( attrUV );
    };
}

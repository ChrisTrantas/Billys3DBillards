#include "MeshLoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

typedef unsigned int UINT;

// Processes an Assimp node
void MeshLoader::ProcessNode( std::vector<Vertex>& vertices, std::vector<UINT>& indices, const aiScene* scene, aiNode* node )
{
    // Process sub-meshes
    for ( UINT i = 0; i < node->mNumMeshes; ++i )
    {
        aiMesh* mesh = scene->mMeshes[ node->mMeshes[ i ] ];
        ProcessMesh( vertices, indices, scene, mesh );
    }

    // Process nodes
    for ( UINT i = 0; i < node->mNumChildren; ++i )
    {
        ProcessNode( vertices, indices, scene, node->mChildren[ i ] );
    }
}

// Processes an Assimp mesh
void MeshLoader::ProcessMesh( std::vector<Vertex>& vertices, std::vector<UINT>& indices, const aiScene* scene, aiMesh* mesh )
{
    // Get the vertices
    Vertex v;
    for ( UINT i = 0; i < mesh->mNumVertices; ++i )
    {
        // Get the vertex position
        v.Position.x = mesh->mVertices[ i ].x;
        v.Position.y = mesh->mVertices[ i ].y;
        v.Position.z = mesh->mVertices[ i ].z;

        // Get the vertex normal
        v.Normal.x = mesh->mNormals[ i ].x;
        v.Normal.y = mesh->mNormals[ i ].y;
        v.Normal.z = mesh->mNormals[ i ].z;

        // Get the vertex tangent
        v.Tangent.x = mesh->mTangents[ i ].x;
        v.Tangent.y = mesh->mTangents[ i ].y;
        v.Tangent.z = mesh->mTangents[ i ].z;

        // Get the vertex texture coordinates (this is assuming a single texture)
        v.UV.x = mesh->mTextureCoords[ 0 ][ i ].x;
        v.UV.y = mesh->mTextureCoords[ 0 ][ i ].y;

        vertices.push_back( v );
    }

    // Get the face indices
    for ( UINT i = 0; i < mesh->mNumFaces; ++i )
    {
        // We triangulate the models, so we're guaranteed 3 indices
        aiFace face = mesh->mFaces[ i ];
        indices.push_back( face.mIndices[ 0 ] );
        indices.push_back( face.mIndices[ 1 ] );
        indices.push_back( face.mIndices[ 2 ] );
    }
}

// Loads a mesh from a file
std::shared_ptr<Mesh> MeshLoader::Load( const std::string& fname )
{
    // Load the mesh's information
    Assimp::Importer importer;
    UINT importFlags = aiProcess_CalcTangentSpace
                     | aiProcess_GenSmoothNormals
                     | aiProcess_JoinIdenticalVertices
                     | aiProcess_Triangulate;
    const aiScene* scene = importer.ReadFile( fname, importFlags );

    // If we failed to load the mesh, then we have nothing to return
    std::shared_ptr<Mesh> mesh;
    if ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
    {
        return mesh;
    }

    // Now process the root node
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    ProcessNode( vertices, indices, scene, scene->mRootNode );

    // Now create the mesh
    mesh = std::make_shared<Mesh>( vertices, indices );
    return mesh;
}

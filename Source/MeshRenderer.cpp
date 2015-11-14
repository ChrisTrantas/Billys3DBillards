#include "MeshRenderer.hpp"
#include <assert.h>

// Create a new mesh renderer
MeshRenderer::MeshRenderer( GameObject* gameObj )
    : Component( gameObj )
{
    _isDrawable = true;

    _mesh = nullptr;
    _material = nullptr;
}

// Destroy this mesh renderer
MeshRenderer::~MeshRenderer()
{
    _material = nullptr;
}

// Set our mesh
void MeshRenderer::SetMesh( std::shared_ptr<Mesh> nMesh )
{
    _mesh = nMesh;
}

// Set our material
void MeshRenderer::SetMaterial( Material* nMaterial )
{
    _material = nMaterial;
}

// Get our mesh
std::shared_ptr<Mesh> MeshRenderer::GetMesh()
{
    return _mesh;
}

// Get our material
Material* MeshRenderer::GetMaterial()
{
    return _material;
}

// Update this mesh renderer
void MeshRenderer::Update()
{
}

// Draw this mesh renderer
void MeshRenderer::Draw()
{
    // Draw the mesh
    if ( _mesh && _material )
    {
        _mesh->Draw( _material );
    }
}

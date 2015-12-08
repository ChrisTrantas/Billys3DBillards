#include "RenderManager.hpp"

std::vector<MeshRenderer*> RenderManager::_meshRenderers;
std::vector<TextRenderer*> RenderManager::_textRenderers;

// Adds the given renderer to be managed
void RenderManager::AddRenderer( MeshRenderer* renderer )
{
    _meshRenderers.push_back( renderer );
}

// Adds the given renderer to be managed
void RenderManager::AddRenderer( TextRenderer* renderer )
{
    _textRenderers.push_back( renderer );
}

// Draws all of the renderer
void RenderManager::Draw()
{
    for ( auto& meshRenderer : _meshRenderers )
    {
        if ( meshRenderer->IsEnabled() && meshRenderer->GetGameObject()->GetActive() )
        {
            meshRenderer->Draw();
        }
    }
    for ( auto& textRenderer : _textRenderers )
    {
        if ( textRenderer->IsEnabled() && textRenderer->GetGameObject()->GetActive() )
        {
            textRenderer->Draw();
        }
    }
}

// Removes the given renderer
void RenderManager::RemoveRenderer( MeshRenderer* renderer )
{
    for ( size_t i = 0; i < _meshRenderers.size(); ++i )
    {
        if ( _meshRenderers[ i ] == renderer )
        {
            _meshRenderers.erase( _meshRenderers.begin() + i );
            break;
        }
    }
}

// Removes the given renderer
void RenderManager::RemoveRenderer( TextRenderer* renderer )
{
    for ( size_t i = 0; i < _textRenderers.size(); ++i )
    {
        if ( _textRenderers[ i ] == renderer )
        {
            _textRenderers.erase( _textRenderers.begin() + i );
            break;
        }
    }
}

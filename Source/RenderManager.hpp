#pragma once

#include "Config.hpp"
#include "MeshRenderer.hpp"
#include "TextRenderer.hpp"
#include <vector>

/// <summary>
/// Defines a render manager.
/// </summary>
class RenderManager
{
    ImplementStaticClass( RenderManager );

private:
    static std::vector<MeshRenderer*> _meshRenderers;
    static std::vector<TextRenderer*> _textRenderers;

public:
    /// <summary>
    /// Adds the given renderer to be managed.
    /// </summary>
    /// <param name="renderer">The renderer.</param>
    static void AddRenderer( MeshRenderer* renderer );

    /// <summary>
    /// Adds the given renderer to be managed.
    /// </summary>
    /// <param name="renderer">The renderer.</param>
    static void AddRenderer( TextRenderer* renderer );

    /// <summary>
    /// Draws all of the renderer.
    /// </summary>
    static void Draw();

    /// <summary>
    /// Removes the given renderer.
    /// </summary>
    /// <param name="renderer">The renderer.</param>
    static void RemoveRenderer( MeshRenderer* renderer );

    /// <summary>
    /// Removes the given renderer.
    /// </summary>
    /// <param name="renderer">The renderer.</param>
    static void RemoveRenderer( TextRenderer* renderer );
};

#pragma once

#include "Component.hpp"
#include "Mesh.hpp"

/// <summary>
/// Defines a Line renderer.
/// </summary>
class LineRenderer : public Component
{
    friend class RenderManager;

private:
    std::shared_ptr<Mesh> _mesh;
    bool _isMeshDirty;

    /// <summary>
    /// Rebuilds our text mesh.
    /// </summary>
    void RebuildMesh();

public:
    /// <summary>
    /// Creates a new text renderer.
    /// </summary>
    /// <param name="gameObject">The game object this component belongs to.</param>
    LineRenderer( GameObject* gameObject );

    /// <summary>
    /// Destroys this text renderer.
    /// </summary>
    ~LineRenderer();

    /// <summary>
    /// Gets the text mesh.
    /// </summary>
    std::shared_ptr<Mesh> GetMesh() const;

    /// <summary>
    /// Gets the text being renderer.
    /// </summary>
    //std::string GetText() const;

    /// <summary>
    /// Checks to see if this text renderer is valid.
    /// </summary>
    bool IsValid() const;

    /// <summary>
    /// Sets the text to be rendered.
    /// </summary>
    /// <param name="value">The new text.</param>
    void SetLine(const std::string& value);

    /// <summary>
    /// Updates this text renderer.
    /// </summary>
    void Update() override;

    /// <summary>
    /// Draws this text renderer.
    /// </summary>
    void Draw() override;
};

#pragma once

#include "Component.hpp"
#include "Font.hpp"
#include "Mesh.hpp"

/// <summary>
/// Defines a text renderer.
/// </summary>
class TextRenderer : public Component
{
    friend class RenderManager;

private:
    std::string _text;
    std::shared_ptr<Font> _font;
    std::shared_ptr<Mesh> _mesh;
    bool _isMeshDirty;

    /// <summary>
    /// Gets the font used by this text renderer.
    /// </summary>
    Font* GetFont();

    /// <summary>
    /// Rebuilds our text mesh.
    /// </summary>
    void RebuildMesh();

public:
    /// <summary>
    /// Creates a new text renderer.
    /// </summary>
    /// <param name="gameObject">The game object this component belongs to.</param>
    TextRenderer( GameObject* gameObject );

    /// <summary>
    /// Destroys this text renderer.
    /// </summary>
    ~TextRenderer();

    /// <summary>
    /// Gets the font used by this text renderer.
    /// </summary>
    const Font* GetFont() const;

    /// <summary>
    /// Gets the current font size.
    /// </summary>
    unsigned int GetFontSize() const;

    /// <summary>
    /// Gets the text mesh.
    /// </summary>
    std::shared_ptr<Mesh> GetMesh() const;

    /// <summary>
    /// Gets the text being renderer.
    /// </summary>
    std::string GetText() const;

    /// <summary>
    /// Checks to see if this text renderer is valid.
    /// </summary>
    bool IsValid() const;

    /// <summary>
    /// Sets this text renderer's font.
    /// </summary>
    /// <param name="value">The new font.</param>
    void SetFont( std::shared_ptr<Font> value );

    /// <summary>
    /// Sets this text renderer's font size.
    /// </summary>
    /// <param name="value">The new font size.</param>
    void SetFontSize( unsigned int value );

    /// <summary>
    /// Sets the text to be rendered.
    /// </summary>
    /// <param name="value">The new text.</param>
    void SetText( const std::string& value );

    /// <summary>
    /// Updates this text renderer.
    /// </summary>
    void Update() override;

    /// <summary>
    /// Draws this text renderer.
    /// </summary>
    void Draw() override;
};

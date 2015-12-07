#pragma once

#include "Material.hpp"

/// <summary>
/// Defines a material to be used when drawing text.
/// </summary>
class TextMaterial : public Material
{
    glm::mat4 _world;
    glm::mat4 _projection;
    glm::vec4 _textColor;
    std::shared_ptr<Texture2D> _fontTexture;

public:
    /// <summary>
    /// Creates a new text material
    /// </summary>
    /// <param name"gameObject">The game object to attach to.</param>
    TextMaterial( GameObject* gameObject );

    /// <summary>
    /// Destroys this text material.
    /// </summary>
    ~TextMaterial();

    /// <summary>
    /// Gets the color to render the text as.
    /// </summary>
    glm::vec4 GetTextColor() const;

    /// <summary>
    /// Sets the color to render the text as.
    /// </summary>
    /// <param name="color">The new color.</param>
    void SetTextColor( const glm::vec4& color );

    void SetWorld( const glm::mat4& world ) { _world = world; }
    void SetProjection( const glm::mat4& proj ) { _projection = proj; }
    void SetFontTexture( std::shared_ptr<Texture2D> texture ) { _fontTexture = texture; }

    /// <summary>
    /// Sends this material's information to the shaders.
    /// </summary>
    void SendValuesToShader() override;
};

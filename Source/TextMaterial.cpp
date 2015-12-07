#include "TextMaterial.hpp"
#include "GameObject.hpp"

// Creates a new text material
TextMaterial::TextMaterial( GameObject* gameObject )
    : Material( gameObject )
    , _textColor( 0, 0, 0, 0 )
{
    // Load the default vertex and pixel shaders
    this->LoadProgram( "Shaders\\TextMaterial.vert", "Shaders\\TextMaterial.frag" );
}

// Destroys this text material
TextMaterial::~TextMaterial()
{
}

// Gets the color to render the text as
glm::vec4 TextMaterial::GetTextColor() const
{
    return _textColor;
}

// Sets the color to render the text as
void TextMaterial::SetTextColor( const glm::vec4& color )
{
    _textColor = color;
}

// Sends this material's information to the shaders
void TextMaterial::SendValuesToShader()
{
    // Send our variables
    SetVec4( "TextColor", _textColor );
    SetMatrix( "World", _world );
    SetMatrix( "Projection", _projection );
    SetTexture( "FontTexture", _fontTexture );
}

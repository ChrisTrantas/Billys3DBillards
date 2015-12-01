#include "SimpleMaterial.hpp"
#include "GameObject.hpp"

// Create a new simple material
SimpleMaterial::SimpleMaterial( GameObject* gameObject )
    : Material( gameObject )
{
    LoadProgram( "Shaders\\SimpleMaterial.vert", "Shaders\\SimpleMaterial.frag" );
}

// Destroy this simple material
SimpleMaterial::~SimpleMaterial()
{
}

// Send our values to the shader
void SimpleMaterial::SendValuesToShader()
{
	SetTexture("MyTexture", _texture);
}

// Set our texture
void SimpleMaterial::SetMyTexture(std::shared_ptr<Texture2D> texture)
{
	_texture = texture;
}

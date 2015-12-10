#include "LineMaterial.hpp"
#include "GameObject.hpp"

// Create a new simple material
LineMaterial::LineMaterial(GameObject* gameObject)
: Material(gameObject)
, _world(1.0f)
{
	LoadProgram("Shaders\\LineMaterial.vert", "Shaders\\LineMaterial.frag");
}

// Destroy this simple material
LineMaterial::~LineMaterial()
{
}

// Send our values to the shader
void LineMaterial::SendValuesToShader()
{
	SetTexture("MyTexture", _texture);
	SetMatrix("World", _world);
}

// Set our texture
void LineMaterial::SetMyTexture(std::shared_ptr<Texture2D> texture)
{
	_texture = texture;
}

// Sets our world matrix
void LineMaterial::SetWorld(const glm::mat4& world)
{
	_world = world;
}

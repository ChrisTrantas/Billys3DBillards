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

#include "LineMaterial.hpp"
#include "GameObject.hpp"

// Create a new simple material
LineMaterial::LineMaterial(GameObject* gameObject)
: Material(gameObject)
, _lineColor( 0,0,0,0)
{
	LoadProgram("Shaders\\LineMaterial.vert", "Shaders\\LineMaterial.frag");

}

// Destroy this simple material
LineMaterial::~LineMaterial()
{
}

glm::vec4 LineMaterial::GetLineColor() const
{
	return _lineColor;
}

void LineMaterial::SetLineColor(const glm::vec4& color)
{
	_lineColor = color;
}

// Send our values to the shader
void LineMaterial::SendValuesToShader()
{
	SetVec4("LineColor", _lineColor);
	SetMatrix("World", _world);
	SetMatrix("Projection", _projection);
}

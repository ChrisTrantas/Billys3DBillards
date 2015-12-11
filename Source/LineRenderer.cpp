#include "LineRenderer.hpp"
#include "LineMaterial.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Vertex.hpp"
#include "Colors.hpp"
#include "Game.hpp"
#include "RenderManager.hpp"
#include <algorithm>
#include <DirectXColors.h>
#include <vector>
#include <iostream>

using namespace DirectX;


// Create a new Line renderer
LineRenderer::LineRenderer(GameObject* gameObject)
: Component(gameObject)
, _isMeshDirty(false)
{
	_isDrawable = true;

	RenderManager::AddRenderer(this);
}

// Destroys this text renderer
LineRenderer::~LineRenderer()
{
	RenderManager::RemoveRenderer(this);
}


// Get our mesh
std::shared_ptr<Mesh> LineRenderer::GetMesh() const
{
	return _mesh;
}

/*
// Check if we're valid
bool LineRenderer::IsValid() const
{
return static_cast<bool>(_font);
}*/

// Rebuild our text mesh (expensive operation)
void LineRenderer::RebuildMesh()
{
	// If there's nothing to do, then... don't do anything
	if (!_isMeshDirty)
	{
		return;
	}

	std::vector<TextVertex> vertices;

	// Create the mesh
	std::vector<unsigned int> indices;
	_mesh = std::make_shared<Mesh>(vertices, indices);
}

void LineRenderer::SetStart(vec2 startPoint)
{
	vec2 _start = startPoint;
};

void LineRenderer::SetEnd(vec2 endPoint)
{
	vec2 _end = endPoint;
};

// Updates this text renderer
void LineRenderer::Update()
{
	if (_isMeshDirty)
	{
		RebuildMesh();
		_isMeshDirty = false;
	}
}

// Draws this text renderer
void LineRenderer::Draw()
{
	LineMaterial* lm = _gameObject->GetComponent<LineMaterial>();
	_mesh->Draw(lm);

	glDepthFunc(GL_LESS);
	glBlendFunc(GL_ONE, GL_ZERO);
}

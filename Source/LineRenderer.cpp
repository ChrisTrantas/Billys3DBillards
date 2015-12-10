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

/*

// Create a new Line renderer
LineMaterial::LineMaterial(GameObject* gameObject)
: Component(gameObject)
, _isMeshDirty(false)
{
	_isDrawable = true;

	RenderManager::AddRenderer(this);
}

// Destroys this text renderer
LineMaterial::~LineMaterial()
{
	RenderManager::RemoveRenderer(this);
}


// Get our mesh
std::shared_ptr<Mesh> LineMaterial::GetMesh() const
{
	return _mesh;
}

// Check if we're valid
bool LineMaterial::IsValid() const
{
	return static_cast<bool>(_font);
}

// Rebuild our text mesh (expensive operation)
void LineMaterial::RebuildMesh()
{
	// If there's nothing to do, then... don't do anything
	if (!_font || _text.empty() || !_isMeshDirty)
	{
		return;
	}



	// Get some helper variables
	const unsigned int fontSize = GetFontSize();
	float xSpace = _font->GetGlyph(' ', fontSize).Advance;
	float ySpace = _font->GetLineSpacing(fontSize);
	float x = 0.0f;
	float y = static_cast<float>(fontSize);
	float uScale = 1.0f / _font->GetTexture(fontSize)->GetWidth();
	float vScale = 1.0f / _font->GetTexture(fontSize)->GetHeight();
	char  chPrev = 0;
	std::vector<TextVertex> vertices;



	// Now go through and create one quad per character
	for (size_t i = 0; i < _text.length(); ++i)
	{
		char chCurr = _text[i];

		// Apply the kerning between the previous and current character
		x += _font->GetKerning(chPrev, chCurr, fontSize);
		chPrev = chCurr;

		// Handle special characters
		if (chCurr == ' ' || chCurr == '\t' || chCurr == '\n' || chCurr == '\r' || chCurr == '\b')
		{
			switch (chCurr)
			{
			case ' ':
				x += xSpace;
				break;
			case '\t':
				x += xSpace * 4;
				break;
			case '\n':
				y += ySpace;
				x = 0.0f;
				break;
			}

			// Now continue to the next glyph
			continue;
		}

		// Get the glyph for the current character
		const Font::Glyph& glyph = _font->GetGlyph(chCurr, fontSize);

		float left = glyph.Bounds.X;
		float top = glyph.Bounds.Y;
		float right = left + glyph.Bounds.Width;
		float bottom = top + glyph.Bounds.Height;

		float u1 = uScale * (glyph.TextureBounds.X);
		float v1 = vScale * (glyph.TextureBounds.Y);
		float u2 = uScale * (glyph.TextureBounds.X + glyph.TextureBounds.Width);
		float v2 = vScale * (glyph.TextureBounds.Y + glyph.TextureBounds.Height);

		// Now add the quad
		vertices.push_back(TextVertex(x + left, y + top, u1, v1));
		vertices.push_back(TextVertex(x + right, y + top, u2, v1));
		vertices.push_back(TextVertex(x + left, y + bottom, u1, v2));
		vertices.push_back(TextVertex(x + left, y + bottom, u1, v2));
		vertices.push_back(TextVertex(x + right, y + top, u2, v1));
		vertices.push_back(TextVertex(x + right, y + bottom, u2, v2));

		// Advance to the next character
		x += glyph.Advance;
	}



	// Create the mesh
	std::vector<unsigned int> indices;
	_mesh = std::make_shared<Mesh>(vertices, indices);
}


// Updates this text renderer
void LineMaterial::Update()
{
	if (_isMeshDirty)
	{
		RebuildMesh();
		_isMeshDirty = false;
	}
}

// Draws this text renderer
void LineMaterial::Draw()
{
	// Draw the mesh
	if (_mesh && _font)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

		TextMaterial* tm = _gameObject->GetComponent<TextMaterial>();
		if (tm)
		{
			GameWindow* window = GameWindow::GetCurrentWindow();
			glm::mat4 proj = glm::ortho(
				0.0f,                                       // left
				static_cast<float>(window->GetWidth()),   // right
				static_cast<float>(window->GetHeight()),  // bottom
				0.0f,                                       // top
				-0.1f,                                      // near
				0.1f                                        // far
				);

			std::shared_ptr<Texture2D> texture = _font->GetTexture(_font->GetCurrentSize());
			if (texture)
			{
				tm->SetWorld(_gameObject->GetWorldMatrix());
				tm->SetProjection(proj);
				tm->SetFontTexture(texture);
			}
		}

		_mesh->Draw(tm);

		glDepthFunc(GL_LESS);
		glBlendFunc(GL_ONE, GL_ZERO);
	}
} 
*/
#pragma once

#include "Config.hpp"
#include "Component.hpp"
#include "Mesh.hpp"
#include "LineMaterial.hpp"

/// <summary>
/// Defines a Line renderer.
/// </summary>
class LineRenderer : public Component
{
	friend class RenderManager;

private:

	LineVertex _points[ 2 ];
	std::shared_ptr<Mesh> _mesh;
	bool _isMeshDirty;

	/// <summary>
	/// Rebuilds our line mesh.
	/// </summary>
	void RebuildMesh();

public:
	/// <summary>
	/// Creates a new line renderer.
	/// </summary>
	/// <param name="gameObject">The game object this component belongs to.</param>
	LineRenderer(GameObject* gameObject);

	/// <summary>
	/// Destroys this Line renderer.
	/// </summary>
	~LineRenderer();

	/// <summary>
	/// Gets the starting point.
	/// </summary>
	glm::vec2 GetStartPoint() const;

	/// <summary>
	/// Gets the ending point.
	/// </summary>
	glm::vec2 GetEndPoint() const;

	/// <summary>
	/// Gets the text mesh.
	/// </summary>
	std::shared_ptr<Mesh> GetMesh() const;


	/// <summary>
	/// Checks to see if this line renderer is valid.
	/// </summary>
	//bool IsValid() const;

	/// <summary>
	/// Sets the line to be rendered.
	/// </summary>
	/// <param name="value">The new text.</param>
	void SetLine(const std::string& value);

	void SetStartPoint(glm::vec2& startPoint);

	void SetEndPoint(glm::vec2& endPoint);

	/// <summary>
	/// Updates this line renderer.
	/// </summary>
	void Update() override;

	/// <summary>
	/// Draws this line renderer.
	/// </summary>
	void Draw() override;
};

#pragma once

#include "Material.hpp"

/// <summary>
/// Defines a simple material.
/// </summary>
class LineMaterial : public Material
{
	glm::mat4 _world;
	glm::mat4 _projection;
	glm::vec4 _lineColor;

public:
	/// <summary>
	/// Creates a new simple material.
	/// </summary>
	/// <param name="gameObject">The game object this material will belong to.</param>
	LineMaterial(GameObject* gameObject);

	/// <summary>
	/// Destroys this simple material.
	/// </summary>
	~LineMaterial();

	/// <summary>
	/// Gets the color to render the line as.
	/// </summary>
	glm::vec4 GetLineColor() const;

	/// <summary>
	/// Sets the color to render the line as.
	/// </summary>
	/// <param name="color">The new color.</param>
	void SetLineColor(const glm::vec4& color);

	void SetWorld(const glm::mat4& world) { _world = world; }

	void SetProjection(const glm::mat4& proj) { _projection = proj; }

	/// <summary>
	/// Sends this material's information to the shaders.
	/// </summary>
	//void UpdateShaderData() override;

	/// <summary>
	/// Sends this material's values to the shader.
	/// </summary>
	void SendValuesToShader() override;

	/// <summary>
	/// Sets the texture this simple material uses.
	/// </summary>
	/// <param name="texture">The texture to use.</param>
	//void SetMyTexture(std::shared_ptr<Texture2D> texture);

	/// <summary>
	/// Sets the world matrix simple material uses.
	/// </summary>
	/// <param name="world">The world matrix.</param>
	
};

#pragma once

#include "Material.hpp"

/// <summary>
/// Defines a simple material.
/// </summary>
class SimpleMaterial : public Material
{
    glm::mat4 _world;
	std::shared_ptr<Texture2D> _texture;

public:
    /// <summary>
    /// Creates a new simple material.
    /// </summary>
    /// <param name="gameObject">The game object this material will belong to.</param>
    SimpleMaterial( GameObject* gameObject );

    /// <summary>
    /// Destroys this simple material.
    /// </summary>
    ~SimpleMaterial();
	
	/// <summary>
	/// Sends this material's values to the shader.
	/// </summary>
	void SendValuesToShader() override;

	/// <summary>
	/// Sets the texture this simple material uses.
	/// </summary>
	/// <param name="texture">The texture to use.</param>
	void SetMyTexture( std::shared_ptr<Texture2D> texture );

    /// <summary>
    /// Sets the world matrix simple material uses.
    /// </summary>
    /// <param name="world">The world matrix.</param>
    void SetWorld( const glm::mat4& world );
};

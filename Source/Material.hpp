#pragma once

#include "Shader.h"
#include "Component.hpp"
#include <memory> // for std::shared_ptr
#include <unordered_map>

class Camera;
class Texture2D;

/// <summary>
/// Defines a material.
/// </summary>
class Material : public Component
{
    // Disallow the copy constructor and assignment operator
    Material( const Material& ) = delete;
    Material& operator=( const Material& ) = delete;

    // Disallow the move constructor and assignment operator
    Material( Material&& ) = delete;
    Material& operator=( Material&& ) = delete;

protected:
    mutable std::unordered_map<std::string, GLint> _attributes;
    mutable std::unordered_map<std::string, GLint> _uniforms;
    GLuint _program;

    /// <summary>
    /// Gets a uniform's location.
    /// </summary>
    /// <param name="name">The uniform name.</param>
    GLint GetUniformLocation( const std::string& name ) const;

    /// <summary>
    /// Loads the shader program
    /// </summary>
    /// <param name="vertShaderFName">The vertex shader name.</param>
    /// <param name="fragShaderFName">The fragment shader name.</param>
    void LoadProgram( const std::string& vertShaderFName, const std::string& fragShaderFName );

public:
    /// <summary>
    /// Creates a new, empty material component.
    /// </summary>
    /// <param name="gameObject">The game object we are being added to.</param>
    Material( GameObject* gameObject );

    /// <summary>
    /// Destroys this material.
    /// </summary>
    virtual ~Material();

    /// <summary>
    /// Activates this material to be the current material.
    /// </summary>
    void Activate() const;

    /// <summary>
    /// Applies the given camera to this material.
    /// </summary>
    /// <param name="camera">The camera to apply.</param>
    void ApplyCamera( const Camera* camera );

    /// <summary>
    /// Gets this material's program ID.
    /// </summary>
    GLuint GetProgramID() const { return _program; }

    /// <summary>
    /// Gets an attribute's location.
    /// </summary>
    /// <param name="name">The uniform name.</param>
    GLint Material::GetAttributeLocation( const std::string& name ) const;

    /// <summary>
    /// Sets a vector in this material.
    /// </summary>
    /// <param name="name">The vector name.</param>
    /// <param name="value">The vector value.</param>
    void SetVec2( const std::string& name, const glm::vec2& value );

    /// <summary>
    /// Sets a vector in this material.
    /// </summary>
    /// <param name="name">The vector name.</param>
    /// <param name="value">The vector value.</param>
    void SetVec3( const std::string& name, const glm::vec2& value );

    /// <summary>
    /// Sets a vector in this material.
    /// </summary>
    /// <param name="name">The vector name.</param>
    /// <param name="value">The vector value.</param>
    void SetVec4( const std::string& name, const glm::vec2& value );

    /// <summary>
    /// Sets a matrix in this material.
    /// </summary>
    /// <param name="name">The matrix name.</param>
    /// <param name="value">The matrix value.</param>
    void SetMatrix( const std::string& name, const glm::mat4& value );

    /// <summary>
    /// Sets a texture in this material.
    /// </summary>
    /// <param name="name">The texture name.</param>
    /// <param name="value">The texture value.</param>
    void SetTexture( const std::string& name, const std::shared_ptr<Texture2D> value );

    void Update() override;
};

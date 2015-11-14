#pragma once

#include "Shader.h"
#include "Component.hpp"
#include <memory> // for std::shared_ptr
#include <unordered_map>

class Camera; // forward declaration

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
    std::unordered_map<std::string, unsigned int> _uniforms;
    GLuint _program;

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
    void Activate();

    /// <summary>
    /// Applies the given camera to this material.
    /// </summary>
    /// <param name="camera">The camera to apply.</param>
    void ApplyCamera( const Camera* camera );

    /// <summary>
    /// Sets a matrix in this material.
    /// </summary>
    /// <param name="name">The matrix name.</param>
    /// <param name="value">The matrix value.</param>
    void SetMatrix( const std::string& name, const glm::mat4& value );
};

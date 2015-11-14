#include "Material.hpp"
#include "Camera.h"
#include "GameObject.hpp"
#include "Shader.h"
#include <assert.h>

// Create a new material
Material::Material( GameObject* gameObject )
    : Component( gameObject )
    , _program( 0 )
{
    _usesLateUpdate = false;    // We don't update
    _isDrawable = false;        // We're not drawable
}

// Destroy this material
Material::~Material()
{
    if ( _program )
    {
        glDeleteProgram( _program );
        _program = 0;
    }
}

// Activates this material
void Material::Activate()
{
    glUseProgram( _program );
}

// Apply a camera to this material
void Material::ApplyCamera( const Camera* camera )
{
    SetMatrix( "View", camera->GetView() );
    SetMatrix( "Projection", camera->GetProjection() );
}

// Load the shader program
void Material::LoadProgram( const std::string& vertShaderFName, const std::string& fragShaderFName )
{
    _uniforms.clear();
    _program = Shader::loadShaderProgram( vertShaderFName.c_str(), fragShaderFName.c_str() );

    if ( _program )
    {
        glm::mat4 identity = glm::mat4( 1.0f );
        SetMatrix( "View", identity );
        SetMatrix( "Projection", identity );
    }
}

// Set a matrix in the material
void Material::SetMatrix( const std::string& name, const glm::mat4& value )
{
    unsigned int location = 0;
    
    auto search = _uniforms.find( name );
    if ( search != _uniforms.end() )
    {
        location = search->second;
    }
    else
    {
        location = glGetUniformLocation( _program, name.c_str() );
        _uniforms[ name ] = location;
    }

    glProgramUniformMatrix4fv( _program, location, 1, GL_FALSE, glm::value_ptr( value ) );
}

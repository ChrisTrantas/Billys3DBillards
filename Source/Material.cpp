#include "Material.hpp"
#include "Camera.h"
#include "GameObject.hpp"
#include "Shader.h"
#include <assert.h>
#include "Texture2D.hpp"

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
void Material::Activate() const
{
    glUseProgram( _program );
}

// Apply a camera to this material
void Material::ApplyCamera( const Camera* camera )
{
    SetMatrix( "View", camera->GetView() );
    SetMatrix( "Projection", camera->GetProjection() );
}

// Gets a uniform's location
GLint Material::GetUniformLocation( const std::string& name ) const
{
    GLint location = 0;

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

    return location;
}

// Gets a uniform's location
GLint Material::GetAttributeLocation( const std::string& name ) const
{
    GLint location = 0;

    auto search = _attributes.find( name );
    if ( search != _attributes.end() )
    {
        location = search->second;
    }
    else
    {
        location = glGetAttribLocation( _program, name.c_str() );
        _attributes[ name ] = location;
    }

    return location;
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
    GLint location = GetUniformLocation( name );
    glProgramUniformMatrix4fv( _program, location, 1, GL_FALSE, glm::value_ptr( value ) );
}

// Set a vec2
void Material::SetVec2( const std::string& name, const glm::vec2& value )
{
    GLint location = GetUniformLocation( name );
    glProgramUniform2fv( _program, location, 1, glm::value_ptr( value ) );
}

// Set a vec3
void Material::SetVec3( const std::string& name, const glm::vec3& value )
{
    GLint location = GetUniformLocation( name );
    glProgramUniform3fv( _program, location, 1, glm::value_ptr( value ) );
}

// Set a vec4
void Material::SetVec4( const std::string& name, const glm::vec4& value )
{
    GLint location = GetUniformLocation( name );
    glProgramUniform4fv( _program, location, 1, glm::value_ptr( value ) );
}

// Set a Texture2D
void Material::SetTexture( const std::string& name, const std::shared_ptr<Texture2D> value )
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, value->GetHandle());

    GLint location = GetUniformLocation( name );
	glProgramUniform1i(_program, location, 0);
}

void Material::Update()
{
}

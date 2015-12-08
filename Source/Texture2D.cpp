#include "Texture2D.hpp"

std::unordered_map<std::string, std::shared_ptr<Texture2D>> Texture2D::_textureCache;

// Create an empty texture
std::shared_ptr<Texture2D> Texture2D::Create( unsigned int width, unsigned int height )
{
    return std::shared_ptr<Texture2D>( new (std::nothrow) Texture2D( width, height, nullptr, false ) );
}

// Load a texture from a file
std::shared_ptr<Texture2D> Texture2D::FromFile( const std::string& fname )
{
    // We don't need to re-load textures
    auto search = _textureCache.find( fname );
    if ( search != _textureCache.end() )
    {
        return search->second;
    }

    std::shared_ptr<Texture2D> texture;

    // Attempt to load the file as an image
    Image image;
    if ( image.LoadFromFile( fname ) )
    {
        return Texture2D::FromImage( image );
    }

    return texture;
}

// Load a texture from an image
std::shared_ptr<Texture2D> Texture2D::FromImage( const Image& image )
{
    unsigned int width  = image.GetWidth();
    unsigned int height = image.GetHeight();
    const void*  pixels = image.GetPixels();
    return std::shared_ptr<Texture2D>( new (std::nothrow) Texture2D( width, height, pixels, true ) );
}

// Create an empty 2D texture
Texture2D::Texture2D( unsigned int width, unsigned int height, const void* data, bool genMipMaps )
    : _texture( 0 )
    , _width( width )
    , _height( height )
{
    glGenTextures( 1, &_texture );
    glBindTexture( GL_TEXTURE_2D, _texture );
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glBindTexture( GL_TEXTURE_2D, 0 );
}

// Destroy this 2D texture
Texture2D::~Texture2D()
{
    glDeleteTextures( 1, &_texture );
}

// Gets this texture's handle
GLuint Texture2D::GetHandle() const
{
    return _texture;
}

// Get the texture's height
unsigned int Texture2D::GetHeight() const
{
    return _width;
}

// Get the texture's width
unsigned int Texture2D::GetWidth() const
{
    return _height;
}

// Updates the given area of the texture
void Texture2D::UpdateArea( unsigned int x, unsigned int y, unsigned int width, unsigned int height, const void* data )
{
    if ( data )
    {
        int xi = static_cast<int>( x );
        int yi = static_cast<int>( y );
        int wi = static_cast<int>( width );
        int hi = static_cast<int>( height );

        if ( glTextureSubImage2D )
        {
            glTextureSubImage2D( _texture, 0, xi, yi, wi, hi, GL_RGBA, GL_UNSIGNED_BYTE, data );
        }
        else
        {
            glBindTexture( GL_TEXTURE_2D, _texture );
            glTexSubImage2D( GL_TEXTURE_2D, 0, xi, yi, wi, hi, GL_RGBA, GL_UNSIGNED_BYTE, data );
            glBindTexture( GL_TEXTURE_2D, 0 );
        }
    }
}

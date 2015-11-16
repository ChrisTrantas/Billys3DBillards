#include "Texture2D.hpp"

// Create an empty texture
std::shared_ptr<Texture2D> Texture2D::Create( unsigned int width, unsigned int height )
{
    return std::shared_ptr<Texture2D>( new (std::nothrow) Texture2D( width, height, nullptr, false ) );
}

// Load a texture from a file
std::shared_ptr<Texture2D> Texture2D::FromFile( const std::string& fname )
{
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
    

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data);


    glBindTexture( GL_TEXTURE_2D, 0 );
}

// Destroy this 2D texture
Texture2D::~Texture2D()
{
    glDeleteTextures( 1, &_texture );
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
    // TODO - This!
}

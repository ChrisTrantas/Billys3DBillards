#pragma once

#include <string>
#include <vector>

/// <summary>
/// Defines an image.
/// </summary>
class Image
{
    friend class Font;
    friend class Texture2D;

    std::vector<unsigned char> _pixels;
    unsigned int _width;
    unsigned int _height;

    /// <summary>
    /// Disposes of any current pixel information.
    /// </summary>
    void Dispose();

public:
    /// <summary>
    /// Creates a new image.
    /// </summary>
    Image();

    /// <summary>
    /// Destroys this image.
    /// </summary>
    ~Image();

    /// <summary>
    /// Gets this image's pixels.
    /// </summary>
    const unsigned char* GetPixels() const;

    /// <summary>
    /// Gets this image's height.
    /// </summary>
    unsigned int GetHeight() const;

    /// <summary>
    /// Gets this image's width.
    /// </summary>
    unsigned int GetWidth() const;

    /// <summary>
    /// Attempts to save this image's data to the given file.
    /// </summary>
    /// <param name="fname">The file name.</param>
    bool Save( const std::string& fname ) const;

    /// <summary>
    /// Attempts to load image data from the given file.
    /// </summary>
    /// <param name="fname">The file name.</param>
    bool LoadFromFile( const std::string& fname );

    /// <summary>
    /// Attempts to load image data from the given texture.
    /// </summary>
    /// <param name="texture">The texture.</param>
    bool LoadFromTexture( const Texture2D& texture );
};

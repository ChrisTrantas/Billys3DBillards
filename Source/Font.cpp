/************************************************************************************
*                                                                                  *
* This class and its implementation are based off of SFML's font implementation.   *
* https://github.com/SFML/SFML/blob/master/include/SFML/Graphics/Font.hpp          *
* https://github.com/SFML/SFML/blob/master/src/SFML/Graphics/Font.cpp              *
*                                                                                  *
************************************************************************************/

#include "Font.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#if defined( _DEBUG ) || defined( DEBUG )
#   include <iostream>
#endif

// Helper macro for a Font's FreeType library
#define _myLibrary reinterpret_cast<FT_Library>( _library )

// Helper macro for a Font's FreeType font face
#define _myFontFace reinterpret_cast<FT_Face>( _fontFace )

// The scale needed for non-bitmap fonts
static const float KerningScale = 1.0f / ( 1 << 6 );

#pragma region Font Structures

// Creates a new glyph
Font::Glyph::Glyph()
    : Advance( 0.0f )
{
}

// Destroys this glyph
Font::Glyph::~Glyph()
{
    Advance = 0.0f;
}

// Create a new, empty glyph row
Font::GlyphRow::GlyphRow()
    : GlyphRow( 0, 0, 0 )
{
}

// Create a new glyph row
Font::GlyphRow::GlyphRow( unsigned int y, unsigned int height, unsigned int width )
    : Y( y )
    , Height( height )
    , Width( width )
{
}

// Destroys this glyph row 
Font::GlyphRow::~GlyphRow()
{
    Y = 0;
    Width = 0;
    Height = 0;
}

// Create a new glyph page
Font::GlyphPage::GlyphPage()
    : NextRowY( 2 )
{
}

// Destroy this glyph page
Font::GlyphPage::~GlyphPage()
{
    NextRowY = 0;
}

// Get a normalized rectangle
FloatRect Font::GlyphPage::GetNormalizedRect( const UintRect& rect )
{
    if ( !this->Texture )
    {
        return FloatRect( 0, 0, 0, 0 );
    }

    float invWidth = 1.0f / this->Texture->GetWidth();
    float invHeight = 1.0f / this->Texture->GetHeight();

    return FloatRect( rect.X * invWidth,
                      rect.Y * invHeight,
                      rect.Width * invWidth,
                      rect.Height * invHeight );
}

#pragma endregion

// Creates a new, empty font
Font::Font()
    : _fontName( "" )
    , _library( nullptr )
    , _fontFace( nullptr )
{
}

// Destroys this font
Font::~Font()
{
    Dispose();
}

// Finds a suitable location for a glyph on a page
UintRect Font::FindGlyphRect( GlyphPage& page, unsigned int width, unsigned int height ) const
{
    // First we need to ensure the glyph page has a texture
    if ( !page.Texture )
    {
        page.Texture = Texture2D::Create( 256U, 256U );
    }

    // Attempt to find the best-fit row
    GlyphRow* bestRow = nullptr;
    float     bestRatio = 0.0f;
    for ( auto iter = page.Rows.begin(); iter != page.Rows.end(); ++iter )
    {
        float ratio = static_cast<float>( height ) / iter->Height;

        // Ignore too small or too tall rows
        if ( ratio < 0.7f || ratio > 1.0f )
        {
            continue;
        }

        // Check if there's enough horizontal space left in the row
        if ( width > page.Texture->GetWidth() - iter->Width )
        {
            continue;
        }

        // Finally, make sure this is the best row
        if ( ratio >= bestRatio )
        {
            bestRow = &( *iter );
            bestRatio = ratio;
        }
    }

    // If we didn't find a good row, then we need to create a new one that is 10% taller than the glyph
    if ( !bestRow )
    {
        unsigned int maxTextureSize = 0;
        glGetIntegerv( GL_MAX_TEXTURE_SIZE, reinterpret_cast<GLint*>( &maxTextureSize ) );
        
        unsigned int rowHeight = height + height / 10;
        while ( ( page.NextRowY + rowHeight >= page.Texture->GetHeight() ) || ( width >= page.Texture->GetWidth() ) )
        {
            // If we don't have enough space, resize the texture
            unsigned int textureWidth = page.Texture->GetWidth();
            unsigned int textureHeight = page.Texture->GetHeight();
            if ( ( textureWidth * 2 <= maxTextureSize ) && ( textureHeight * 2 <= maxTextureSize ) )
            {
                // Load the old texture
                Image oldTexture;
                oldTexture.LoadFromTexture( *page.Texture );

                // Create the new texture
                std::shared_ptr<Texture2D> newTexture = Texture2D::Create( textureWidth * 2, textureHeight * 2 );
                newTexture->UpdateArea( 0, 0, oldTexture.GetWidth(), oldTexture.GetHeight(), &( oldTexture._pixels[ 0 ] ) );

                // Update the texture
                page.Texture = newTexture;
            }
            else
            {
#if defined( _DEBUG ) || defined( DEBUG )
                std::cout << "Could not find a suitable location in the font texture; maximum size reached." << std::endl;
#endif
                return UintRect( 0, 0, 2, 2 );
            }
        }

        // Create and record the row
        page.Rows.push_back( GlyphRow( page.NextRowY, rowHeight ) );
        page.NextRowY += rowHeight;
        bestRow = &page.Rows.back();
    }

    // Get the best-fit rectangle in the row
    UintRect rect = UintRect( bestRow->Width, bestRow->Y, width, height );
    bestRow->Width += width;

    return rect;
}

// Get the font family name
std::string Font::GetFontName() const
{
    return _fontName;
}

// Get the current size
unsigned int Font::GetCurrentSize() const
{
    if ( _fontFace )
    {
        return _myFontFace->size->metrics.x_ppem;
    }
    return 0;
}

// Disposes of this font
void Font::Dispose()
{
    // Cleanup the font face
    if ( _fontFace )
    {
        FT_Done_Face( _myFontFace );
        _fontFace = nullptr;
    }

    // Cleanup the library
    if ( _library )
    {
        FT_Done_FreeType( _myLibrary );
        _library = nullptr;
    }
}

// Get the given character's glyph
Font::Glyph& Font::GetGlyph( char ch, unsigned int size )
{
    GlyphTable& glyphTable = _pages[ size ].Glyphs;

    // If the character already exists
    auto search = glyphTable.find( ch );
    if ( search != glyphTable.end() )
    {
        // Return its glyph
        return search->second;
    }
    else
    {
        // Otherwise we need to add the glyph
        Glyph glyph = LoadGlyph( ch, size );
        return glyphTable.insert( std::make_pair( ch, glyph ) ).first->second;
    }
}

// Get the kerning between two characters
float Font::GetKerning( char first, char second, unsigned int size )
{
    // If anything is invalid, there's no kerning
    if ( first == 0 || second == 0 || size == 0 || !_fontFace )
    {
        return 0.0f;
    }

    if ( FT_HAS_KERNING( _myFontFace ) && SetCurrentSize( size ) )
    {
        // Get the characters as indices
        FT_UInt firstIndex = FT_Get_Char_Index( _myFontFace, first );
        FT_UInt secondIndex = FT_Get_Char_Index( _myFontFace, second );

        // Get the kerning vector
        FT_Vector kerning;
        FT_Get_Kerning( _myFontFace, firstIndex, secondIndex, FT_KERNING_DEFAULT, &kerning );

        // We don't need to apply the kerning scale to bitmap fonts
        float scale = ( FT_IS_SCALABLE( _myFontFace ) ? KerningScale : 1.0f );
        return kerning.x * scale;
    }

    return 0.0f;
}

// Get the spacing between two lines
float Font::GetLineSpacing( unsigned int size )
{
    if ( _fontFace && SetCurrentSize( size ) )
    {
        return _myFontFace->size->metrics.height * KerningScale;
    }

    return 0.0f;
}

// Get the texture for the given size
std::shared_ptr<Texture2D> Font::GetTexture( unsigned int size )
{
    std::shared_ptr<Texture2D> texture;

    // Find the texture in the glyph page for the given font size
    auto search = _pages.find( size );
    if ( search != _pages.end() )
    {
        GlyphPage& page = search->second;
        texture = page.Texture;

        // If the texture doesn't exist, create it
        if ( !texture )
        {
            texture = Texture2D::Create( 256, 256 );
            page.Texture = texture;
        }
    }

    return texture;
}

// Load a character glyph
Font::Glyph Font::LoadGlyph( char ch, unsigned int size )
{
    Glyph glyph;

    // Ensure we can even retrieve the glyph
    if ( !_fontFace || !SetCurrentSize( size ) )
    {
        return glyph;
    }

    // Attempt to load the font's glyph for the given character
    if ( 0 != FT_Load_Char( _myFontFace, ch, FT_LOAD_TARGET_NORMAL | FT_LOAD_FORCE_AUTOHINT ) )
    {
        return glyph;
    }

    // Get the glyph's description
    FT_Glyph ftGlyph;
    if ( 0 != FT_Get_Glyph( _myFontFace->glyph, &ftGlyph ) )
    {
        return glyph;
    }

    // Rasterize the glyph
    FT_Glyph_To_Bitmap( &ftGlyph, FT_RENDER_MODE_NORMAL, 0, 1 );
    FT_Bitmap& bitmap = reinterpret_cast<FT_BitmapGlyph>( ftGlyph )->bitmap;

    // Get the glyph's advance
    glyph.Advance = static_cast<float>( _myFontFace->glyph->metrics.horiAdvance ) * KerningScale;

    int width = bitmap.width;
    int height = bitmap.rows;

    if ( ( width > 0 ) && ( height > 0 ) )
    {
        // Get the glyph's page
        GlyphPage& page = _pages[ size ];

        // Leave a small padding around characters, so that filtering doesn't
        // pollute them with pixels from neighbors
        const unsigned int padding = 1;

        // Find a good position for the new glyph into the texture
        UintRect emptyArea = FindGlyphRect( page, width + 2 * padding, height + 2 * padding );;

        // Ensure the texture data is in the center of the texture rectangle
        emptyArea.X += padding;
        emptyArea.Y += padding;
        emptyArea.Width -= 2 * padding;
        emptyArea.Height -= 2 * padding;
        glyph.TextureBounds = emptyArea;

        // Set the glyph's bounding box
        glyph.Bounds.X = ( _myFontFace->glyph->metrics.horiBearingX ) * KerningScale;
        glyph.Bounds.Y = -( _myFontFace->glyph->metrics.horiBearingY ) * KerningScale;
        glyph.Bounds.Width = ( _myFontFace->glyph->metrics.width ) * KerningScale;
        glyph.Bounds.Height = ( _myFontFace->glyph->metrics.height ) * KerningScale;


        // Extract the glyph's pixels from the bitmap
        _pixelBuffer.resize( width * height * 4, 255 );
        const unsigned char* pixels = bitmap.buffer;
        if ( bitmap.pixel_mode == FT_PIXEL_MODE_MONO )
        {
            // Pixels are 1 bit monochrome values
            for ( int y = 0; y < height; ++y )
            {
                for ( int x = 0; x < width; ++x )
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = ( x + y * width ) * 4 + 3;
                    _pixelBuffer[ index ] = ( ( pixels[ x / 8 ] ) & ( 1 << ( 7 - ( x % 8 ) ) ) ) ? 255 : 0;
                }
                pixels += bitmap.pitch;
            }
        }
        else
        {
            // Pixels are 8 bits gray levels
            for ( int y = 0; y < height; ++y )
            {
                for ( int x = 0; x < width; ++x )
                {
                    // The color channels remain white, just fill the alpha channel
                    std::size_t index = ( x + y * width ) * 4 + 3;
                    _pixelBuffer[ index ] = pixels[ x ];
                }
                pixels += bitmap.pitch;
            }
        }

        // Write the pixels to the texture
        page.Texture->UpdateArea( emptyArea.X, emptyArea.Y, emptyArea.Width, emptyArea.Height, &_pixelBuffer[ 0 ] );
    }

    // Cleanup
    FT_Done_Glyph( ftGlyph );

    return glyph;
}

// Attempts to load font information from a file
bool Font::LoadFromFile( const std::string& fname )
{
    // Remove any loaded information
    Dispose();

    // Attempt to create our FreeType library
    FT_Library library;
    if ( 0 != FT_Init_FreeType( &library ) )
    {
#if defined( _DEBUG ) || defined( DEBUG )
        std::cout << "Failed to initialize FreeType for '" << fname << "'." << std::endl;
#endif
        return false;
    }
    _library = library;

    // Attempt to load the font face
    FT_Face fontFace;
    if ( 0 != FT_New_Face( library, fname.c_str(), 0, &fontFace ) )
    {
#if defined( _DEBUG ) || defined( DEBUG )
        std::cout << "Failed to create font face for '" << fname << "'." << std::endl;
#endif
        return false;
    }
    _fontFace = fontFace;

    // Get the font name
    _fontName = fontFace->family_name ? fontFace->family_name : "N/A";

    // Attempt to select the Unicode character map
    if ( 0 != FT_Select_Charmap( fontFace, FT_ENCODING_UNICODE ) )
    {
#if defined( _DEBUG ) || defined( DEBUG )
        std::cout << "Failed to select unicode font for '" << fname << "'." << std::endl;
#endif
        Dispose();
        return false;
    }

    // Set our default font size to be 12
    SetCurrentSize( 12U );

    return true;
}

// Set the current font size
bool Font::SetCurrentSize( unsigned int size )
{
    unsigned int currentSize = GetCurrentSize();

    // Only change the size if necessary
    if ( currentSize != size )
    {
        FT_Error error = FT_Set_Pixel_Sizes( _myFontFace, 0, size );

#if defined( _DEBUG ) || defined( DEBUG )
        // If the given size was invalid, print out valid sizes
        if ( error == FT_Err_Invalid_Pixel_Size && !FT_IS_SCALABLE( _myFontFace ) )
        {
            std::cout << "Failed to set " << GetFontName() << " font size to " << size << std::endl;
            std::cout << "Valid sizes for " << GetFontName() << ":" << std::endl;
            for ( int i = 0; i < _myFontFace->num_fixed_sizes; ++i )
            {
                std::cout << "  " << _myFontFace->available_sizes[ i ].height << std::endl;
            }
        }
#endif

        return error == FT_Err_Ok;
    }

    return true;
}

// Check if we have valid data
Font::operator bool() const
{
    return ( _fontFace != nullptr )
        && ( _library != nullptr );
}

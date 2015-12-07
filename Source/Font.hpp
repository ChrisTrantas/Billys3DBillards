#pragma once

/************************************************************************************
*                                                                                  *
* This class and its implementation are based off of SFML's font implementation.   *
* https://github.com/SFML/SFML/blob/master/include/SFML/Graphics/Font.hpp          *
* https://github.com/SFML/SFML/blob/master/src/SFML/Graphics/Font.cpp              *
*                                                                                  *
************************************************************************************/

#include "Config.hpp"
#include "Rect.hpp"
#include "Texture2D.hpp"
#include <string>
#include <unordered_map>
#include <vector>

/// <summary>
/// Defines a font.
/// </summary>
class Font
{
    friend class TextRenderer;

    ImplementNonCopyableClass( Font );
    ImplementNonMovableClass( Font );

#pragma region Structures

    /// <summary>
    /// Defines a font glyph.
    /// </summary>
    struct Glyph
    {
        float Advance;
        FloatRect Bounds;
        UintRect TextureBounds;

        /// <summary>
        /// Creates an empty glyph.
        /// </summary>
        Glyph();

        /// <summary>
        /// Destroys this glyph.
        /// </summary>
        ~Glyph();
    };

    /// <summary>
    /// Defines a row of glyphs.
    /// </summary>
    struct GlyphRow
    {
        unsigned int Y;
        unsigned int Width;
        unsigned int Height;

        /// <summary>
        /// Creates an empty glyph row.
        /// </summary>
        GlyphRow();

        /// <summary>
        /// Creates a new glyph row.
        /// </summary>
        /// <param name="y">The initial Y position of the row.</param>
        /// <param name="width">The initial width of the row.</param>
        /// <param name="height">The initial height of the row.</param>
        GlyphRow( unsigned int y, unsigned int height, unsigned int width = 0 );

        /// <summary>
        /// Destroys this glyph row.
        /// </summary>
        ~GlyphRow();
    };

    /// <summary>
    /// Defines a glyph table.
    /// </summary>
    typedef std::unordered_map<char, Glyph> GlyphTable;

    /// <summary>
    /// Defines a page of glyphs.
    /// </summary>
    struct GlyphPage
    {
        GlyphTable Glyphs;
        std::vector<GlyphRow> Rows;
        std::shared_ptr<Texture2D> Texture;
        unsigned int NextRowY;

        /// <summary>
        /// Creates a new glyph page.
        /// </summary>
        GlyphPage();

        /// <summary>
        /// Destroys this glyph page.
        /// </summary>
        ~GlyphPage();

        /// <summary>
        /// Gets the texture coordinate-normalized rectangle version of the given pixel rectangle.
        /// </summary>
        /// <param name="rect">The rectangle.</param>
        FloatRect GetNormalizedRect( const UintRect& rect );
    };

    /// <summary>
    /// Defines a glyph page table.
    /// </summary>
    typedef std::unordered_map<unsigned int, GlyphPage> GlyphPageTable;

#pragma endregion

private:
    GlyphPageTable _pages;
    std::vector<unsigned char> _pixelBuffer;
    std::string _fontName;
    void* _library;
    void* _fontFace;

private:
    /// <summary>
    /// Finds a suitable location for a glyph on a glyph page.
    /// </summary>
    /// <param name="page">The glyph page to search on.</param>
    /// <param name="width">The width of the glyph.</param>
    /// <param name="height">The height of the glyph.</param>
    UintRect FindGlyphRect( GlyphPage& page, unsigned int width, unsigned int height ) const;

    /// <summary>
    /// Disposes of this font.
    /// </summary>
    void Dispose();

    /// <summary>
    /// Gets the glyph for the given character at the given size.
    /// </summary>
    /// <param name="ch">The character.</param>
    /// <param name="size">The character size.</param>
    Glyph& GetGlyph( char ch, unsigned int size );

    /// <summary>
    /// Gets the kerning between two characters.
    /// </summary>
    /// <param name="first">The first character.</param>
    /// <param name="second">The second character.</param>
    /// <param name="size">The character size.</param>
    float GetKerning( char first, char second, unsigned int size );

    /// <summary>
    /// Gets the amount of space between two lines of text.
    /// </summary>
    /// <param name="size">The character size.</param>
    float GetLineSpacing( unsigned int size );

    /// <summary>
    /// Gets the texture used for the given font size.
    /// </summary>
    /// <param name="size">The character size.</param>
    std::shared_ptr<Texture2D> GetTexture( unsigned int size );

    /// <summary>
    /// Loads the glyph for the given character at the given size.
    /// </summary>
    /// <param name="ch">The character.</param>
    /// <param name="size">The character size.</param>
    Glyph LoadGlyph( char ch, unsigned int size );

public:
    /// <summary>
    /// Creates a new font.
    /// </summary>
    Font();

    /// <summary>
    /// Destroys this font.
    /// </summary>
    ~Font();

    /// <summary>
    /// Gets this font's family name.
    /// </summary>
    std::string GetFontName() const;

    /// <summary>
    /// Gets the current size of this font.
    /// </summary>
    unsigned int GetCurrentSize() const;

    /// <summary>
    /// Attempts to load font information from the given file.
    /// </summary>
    /// <param name="fname">The file name.</param>
    bool LoadFromFile( const std::string& fname );

    /// <summary>
    /// Sets the current size of this font.
    /// </summary>
    /// <param name="size">The new size.</param>
    bool SetCurrentSize( unsigned int size );

    /// <summary>
    /// Checks to see if this font contains valid data.
    /// </summary>
    operator bool() const;
};
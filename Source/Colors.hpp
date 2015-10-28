#pragma once

#include "Math.hpp"

/// <summary>
/// Helper macro for defining a color.
/// </summary>
/// <param name="name">The name of the color.</param>
/// <param name="r">The red component of the color.</param>
/// <param name="g">The green component of the color.</param>
/// <param name="b">The blue component of the color.</param>
#define DefineColor(name, r, g, b) static const glm::vec4 name(r, g, b, 1.0f)

/// <summary>
/// A namespace containing pre-defined colors.
/// </summary>
namespace Colors
{
    DefineColor( AliceBlue,             0.941176534f, 0.972549081f, 1.000000000f );
    DefineColor( AntiqueWhite,          0.980392218f, 0.921568692f, 0.843137324f );
    DefineColor( Aqua,                  0.000000000f, 1.000000000f, 1.000000000f );
    DefineColor( Aquamarine,            0.498039246f, 1.000000000f, 0.831372619f );
    DefineColor( Azure,                 0.941176534f, 1.000000000f, 1.000000000f );
    DefineColor( Beige,                 0.960784376f, 0.960784376f, 0.862745166f );
    DefineColor( Bisque,                1.000000000f, 0.894117713f, 0.768627524f );
    DefineColor( Black,                 0.000000000f, 0.000000000f, 0.000000000f );
    DefineColor( BlanchedAlmond,        1.000000000f, 0.921568692f, 0.803921640f );
    DefineColor( Blue,                  0.000000000f, 0.000000000f, 1.000000000f );
    DefineColor( BlueViolet,            0.541176498f, 0.168627456f, 0.886274576f );
    DefineColor( Brown,                 0.647058845f, 0.164705887f, 0.164705887f );
    DefineColor( BurlyWood,             0.870588303f, 0.721568644f, 0.529411793f );
    DefineColor( CadetBlue,             0.372549027f, 0.619607866f, 0.627451003f );
    DefineColor( Chartreuse,            0.498039246f, 1.000000000f, 0.000000000f );
    DefineColor( Chocolate,             0.823529482f, 0.411764741f, 0.117647067f );
    DefineColor( Coral,                 1.000000000f, 0.498039246f, 0.313725501f );
    DefineColor( CornflowerBlue,        0.392156899f, 0.584313750f, 0.929411829f );
    DefineColor( Cornsilk,              1.000000000f, 0.972549081f, 0.862745166f );
    DefineColor( Crimson,               0.862745166f, 0.078431375f, 0.235294133f );
    DefineColor( Cyan,                  0.000000000f, 1.000000000f, 1.000000000f );
    DefineColor( DarkBlue,              0.000000000f, 0.000000000f, 0.545098066f );
    DefineColor( DarkCyan,              0.000000000f, 0.545098066f, 0.545098066f );
    DefineColor( DarkGoldenrod,         0.721568644f, 0.525490224f, 0.043137256f );
    DefineColor( DarkGray,              0.662745118f, 0.662745118f, 0.662745118f );
    DefineColor( DarkGreen,             0.000000000f, 0.392156899f, 0.000000000f );
    DefineColor( DarkKhaki,             0.741176486f, 0.717647076f, 0.419607878f );
    DefineColor( DarkMagenta,           0.545098066f, 0.000000000f, 0.545098066f );
    DefineColor( DarkOliveGreen,        0.333333343f, 0.419607878f, 0.184313729f );
    DefineColor( DarkOrange,            1.000000000f, 0.549019635f, 0.000000000f );
    DefineColor( DarkOrchid,            0.600000024f, 0.196078449f, 0.800000072f );
    DefineColor( DarkRed,               0.545098066f, 0.000000000f, 0.000000000f );
    DefineColor( DarkSalmon,            0.913725555f, 0.588235319f, 0.478431404f );
    DefineColor( DarkSeaGreen,          0.560784340f, 0.737254918f, 0.545098066f );
    DefineColor( DarkSlateBlue,         0.282352954f, 0.239215702f, 0.545098066f );
    DefineColor( DarkSlateGray,         0.184313729f, 0.309803933f, 0.309803933f );
    DefineColor( DarkTurquoise,         0.000000000f, 0.807843208f, 0.819607913f );
    DefineColor( DarkViolet,            0.580392182f, 0.000000000f, 0.827451050f );
    DefineColor( DeepPink,              1.000000000f, 0.078431375f, 0.576470613f );
    DefineColor( DeepSkyBlue,           0.000000000f, 0.749019623f, 1.000000000f );
    DefineColor( DimGray,               0.411764741f, 0.411764741f, 0.411764741f );
    DefineColor( DodgerBlue,            0.117647067f, 0.564705908f, 1.000000000f );
    DefineColor( Firebrick,             0.698039234f, 0.133333340f, 0.133333340f );
    DefineColor( FloralWhite,           1.000000000f, 0.980392218f, 0.941176534f );
    DefineColor( ForestGreen,           0.133333340f, 0.545098066f, 0.133333340f );
    DefineColor( Fuchsia,               1.000000000f, 0.000000000f, 1.000000000f );
    DefineColor( Gainsboro,             0.862745166f, 0.862745166f, 0.862745166f );
    DefineColor( GhostWhite,            0.972549081f, 0.972549081f, 1.000000000f );
    DefineColor( Gold,                  1.000000000f, 0.843137324f, 0.000000000f );
    DefineColor( Goldenrod,             0.854902029f, 0.647058845f, 0.125490203f );
    DefineColor( Gray,                  0.501960814f, 0.501960814f, 0.501960814f );
    DefineColor( Green,                 0.000000000f, 0.501960814f, 0.000000000f );
    DefineColor( GreenYellow,           0.678431392f, 1.000000000f, 0.184313729f );
    DefineColor( Honeydew,              0.941176534f, 1.000000000f, 0.941176534f );
    DefineColor( HotPink,               1.000000000f, 0.411764741f, 0.705882370f );
    DefineColor( IndianRed,             0.803921640f, 0.360784322f, 0.360784322f );
    DefineColor( Indigo,                0.294117659f, 0.000000000f, 0.509803951f );
    DefineColor( Ivory,                 1.000000000f, 1.000000000f, 0.941176534f );
    DefineColor( Khaki,                 0.941176534f, 0.901960850f, 0.549019635f );
    DefineColor( Lavender,              0.901960850f, 0.901960850f, 0.980392218f );
    DefineColor( LavenderBlush,         1.000000000f, 0.941176534f, 0.960784376f );
    DefineColor( LawnGreen,             0.486274540f, 0.988235354f, 0.000000000f );
    DefineColor( LemonChiffon,          1.000000000f, 0.980392218f, 0.803921640f );
    DefineColor( LightBlue,             0.678431392f, 0.847058892f, 0.901960850f );
    DefineColor( LightCoral,            0.941176534f, 0.501960814f, 0.501960814f );
    DefineColor( LightCyan,             0.878431439f, 1.000000000f, 1.000000000f );
    DefineColor( LightGoldenrodYellow,  0.980392218f, 0.980392218f, 0.823529482f );
    DefineColor( LightGreen,            0.564705908f, 0.933333397f, 0.564705908f );
    DefineColor( LightGray,             0.827451050f, 0.827451050f, 0.827451050f );
    DefineColor( LightPink,             1.000000000f, 0.713725507f, 0.756862819f );
    DefineColor( LightSalmon,           1.000000000f, 0.627451003f, 0.478431404f );
    DefineColor( LightSeaGreen,         0.125490203f, 0.698039234f, 0.666666687f );
    DefineColor( LightSkyBlue,          0.529411793f, 0.807843208f, 0.980392218f );
    DefineColor( LightSlateGray,        0.466666698f, 0.533333361f, 0.600000024f );
    DefineColor( LightSteelBlue,        0.690196097f, 0.768627524f, 0.870588303f );
    DefineColor( LightYellow,           1.000000000f, 1.000000000f, 0.878431439f );
    DefineColor( Lime,                  0.000000000f, 1.000000000f, 0.000000000f );
    DefineColor( LimeGreen,             0.196078449f, 0.803921640f, 0.196078449f );
    DefineColor( Linen,                 0.980392218f, 0.941176534f, 0.901960850f );
    DefineColor( Magenta,               1.000000000f, 0.000000000f, 1.000000000f );
    DefineColor( Maroon,                0.501960814f, 0.000000000f, 0.000000000f );
    DefineColor( MediumAquamarine,      0.400000036f, 0.803921640f, 0.666666687f );
    DefineColor( MediumBlue,            0.000000000f, 0.000000000f, 0.803921640f );
    DefineColor( MediumOrchid,          0.729411781f, 0.333333343f, 0.827451050f );
    DefineColor( MediumPurple,          0.576470613f, 0.439215720f, 0.858823597f );
    DefineColor( MediumSeaGreen,        0.235294133f, 0.701960802f, 0.443137288f );
    DefineColor( MediumSlateBlue,       0.482352972f, 0.407843173f, 0.933333397f );
    DefineColor( MediumSpringGreen,     0.000000000f, 0.980392218f, 0.603921592f );
    DefineColor( MediumTurquoise,       0.282352954f, 0.819607913f, 0.800000072f );
    DefineColor( MediumVioletRed,       0.780392230f, 0.082352944f, 0.521568656f );
    DefineColor( MidnightBlue,          0.098039225f, 0.098039225f, 0.439215720f );
    DefineColor( MintCream,             0.960784376f, 1.000000000f, 0.980392218f );
    DefineColor( MistyRose,             1.000000000f, 0.894117713f, 0.882353008f );
    DefineColor( Moccasin,              1.000000000f, 0.894117713f, 0.709803939f );
    DefineColor( NavajoWhite,           1.000000000f, 0.870588303f, 0.678431392f );
    DefineColor( Navy,                  0.000000000f, 0.000000000f, 0.501960814f );
    DefineColor( OldLace,               0.992156923f, 0.960784376f, 0.901960850f );
    DefineColor( Olive,                 0.501960814f, 0.501960814f, 0.000000000f );
    DefineColor( OliveDrab,             0.419607878f, 0.556862772f, 0.137254909f );
    DefineColor( Orange,                1.000000000f, 0.647058845f, 0.000000000f );
    DefineColor( OrangeRed,             1.000000000f, 0.270588249f, 0.000000000f );
    DefineColor( Orchid,                0.854902029f, 0.439215720f, 0.839215755f );
    DefineColor( PaleGoldenrod,         0.933333397f, 0.909803987f, 0.666666687f );
    DefineColor( PaleGreen,             0.596078455f, 0.984313786f, 0.596078455f );
    DefineColor( PaleTurquoise,         0.686274529f, 0.933333397f, 0.933333397f );
    DefineColor( PaleVioletRed,         0.858823597f, 0.439215720f, 0.576470613f );
    DefineColor( PapayaWhip,            1.000000000f, 0.937254965f, 0.835294187f );
    DefineColor( PeachPuff,             1.000000000f, 0.854902029f, 0.725490212f );
    DefineColor( Peru,                  0.803921640f, 0.521568656f, 0.247058839f );
    DefineColor( Pink,                  1.000000000f, 0.752941251f, 0.796078503f );
    DefineColor( Plum,                  0.866666734f, 0.627451003f, 0.866666734f );
    DefineColor( PowderBlue,            0.690196097f, 0.878431439f, 0.901960850f );
    DefineColor( Purple,                0.501960814f, 0.000000000f, 0.501960814f );
    DefineColor( Red,                   1.000000000f, 0.000000000f, 0.000000000f );
    DefineColor( RosyBrown,             0.737254918f, 0.560784340f, 0.560784340f );
    DefineColor( RoyalBlue,             0.254901975f, 0.411764741f, 0.882353008f );
    DefineColor( SaddleBrown,           0.545098066f, 0.270588249f, 0.074509807f );
    DefineColor( Salmon,                0.980392218f, 0.501960814f, 0.447058856f );
    DefineColor( SandyBrown,            0.956862807f, 0.643137276f, 0.376470625f );
    DefineColor( SeaGreen,              0.180392161f, 0.545098066f, 0.341176480f );
    DefineColor( SeaShell,              1.000000000f, 0.960784376f, 0.933333397f );
    DefineColor( Sienna,                0.627451003f, 0.321568638f, 0.176470593f );
    DefineColor( Silver,                0.752941251f, 0.752941251f, 0.752941251f );
    DefineColor( SkyBlue,               0.529411793f, 0.807843208f, 0.921568692f );
    DefineColor( SlateBlue,             0.415686309f, 0.352941185f, 0.803921640f );
    DefineColor( SlateGray,             0.439215720f, 0.501960814f, 0.564705908f );
    DefineColor( Snow,                  1.000000000f, 0.980392218f, 0.980392218f );
    DefineColor( SpringGreen,           0.000000000f, 1.000000000f, 0.498039246f );
    DefineColor( SteelBlue,             0.274509817f, 0.509803951f, 0.705882370f );
    DefineColor( Tan,                   0.823529482f, 0.705882370f, 0.549019635f );
    DefineColor( Teal,                  0.000000000f, 0.501960814f, 0.501960814f );
    DefineColor( Thistle,               0.847058892f, 0.749019623f, 0.847058892f );
    DefineColor( Tomato,                1.000000000f, 0.388235331f, 0.278431386f );
    DefineColor( Transparent,           0.000000000f, 0.000000000f, 0.000000000f );
    DefineColor( Turquoise,             0.250980407f, 0.878431439f, 0.815686345f );
    DefineColor( Violet,                0.933333397f, 0.509803951f, 0.933333397f );
    DefineColor( Wheat,                 0.960784376f, 0.870588303f, 0.701960802f );
    DefineColor( White,                 1.000000000f, 1.000000000f, 1.000000000f );
    DefineColor( WhiteSmoke,            0.960784376f, 0.960784376f, 0.960784376f );
    DefineColor( Yellow,                1.000000000f, 1.000000000f, 0.000000000f );
    DefineColor( YellowGreen,           0.603921592f, 0.803921640f, 0.196078449f );
}

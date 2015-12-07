#version 440

in vec2 fragUV;

layout(location = 0) out vec4 fragColor;

uniform sampler2D FontTexture;
uniform vec4 TextColor;

void main()
{
    vec2 uv = fragUV;
	uv.y = 1.0 - uv.y;

    vec4 textureColor = texture(FontTexture, uv);
    fragColor = textureColor * TextColor;
}

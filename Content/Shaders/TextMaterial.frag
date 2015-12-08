#version 440

in vec2 fragUV;

layout(location = 0) out vec4 fragColor;

uniform sampler2D FontTexture;
uniform vec4 TextColor;

void main()
{
    vec4 textureColor = texture(FontTexture, fragUV);
    fragColor = vec4(TextColor.rgb, textureColor.a);
}

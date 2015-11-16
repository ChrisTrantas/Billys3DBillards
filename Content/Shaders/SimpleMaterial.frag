#version 430

in vec2 fragUV;

out layout(location = 0) vec4 fragColor;

uniform sampler2D textureSampler;

void main()
{
    vec4 textureColor = texture(textureSampler, fragUV);
    fragColor = textureColor;
}

#version 440

in vec2 fragUV;

layout(location = 0) out vec4 fragColor;

uniform sampler2D MyTexture;

void main()
{
	vec2 uv = fragUV;
	uv.y = 1.0 - uv.y;

    vec4 textureColor = texture(MyTexture, uv);
    fragColor = vec4(textureColor.rgb, 1.0);
    //fragColor = vec4(fragUV, 0, 1);
}

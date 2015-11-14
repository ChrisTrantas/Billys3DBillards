#version 420

in vec4 varyingColor;
uniform vec4 uniformColor;

uniform bool texturedObject;
uniform sampler2D textureSampler;

void main()
{
	gl_FragColor = varyingColor * uniformColor;
	
	if(texturedObject)
	{
		vec2 texCoord = vec2(varyingColor.r,varyingColor.g);
		vec4 textureColor = texture(textureSampler, texCoord);
		gl_FragColor = textureColor * uniformColor;
	}
	
}
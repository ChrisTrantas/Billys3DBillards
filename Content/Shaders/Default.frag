#version 330

uniform float useNormalMap; // Float, treated as bool
// TODO - Diffuse map, normal map

in vec4 fragPosition;
in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragTangent;
in vec3 fragWorldPosition;

out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
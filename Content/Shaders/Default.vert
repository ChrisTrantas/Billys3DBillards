#version 330

uniform mat4 world;
uniform mat4 worldViewProjection;

in vec3 vertPosition;
in vec2 vertUV;
in vec3 vertNormal;
in vec3 vertTangent;

out vec4 fragPosition;
out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragTangent;
out vec3 fragWorldPosition;

void main()
{
    // Calculate the position
    fragPosition = worldViewProjection * vec4(vertPosition, 1.0);

    // Calculate the normal and tangent
    fragNormal  = (mat3)worldViewProjection * vertNormal;
    fragTangent = (mat3)worldViewProjection * vertTangent;

    // Calculate the world position
    fragWorldPosition = (world * vec4(vertPosition, 1.0)).xyz;

    // Pass through the UV coordinates
    fragUV = vertUV;

    // Tell OpenGL the vertex position
    gl_Position = fragPosition;
}

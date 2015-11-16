#version 430

in vec3 vertPosition;
in vec3 vertNormal;
in vec3 vertTangent;
in vec2 vertUV;

out vec2 fragUV;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    fragUV = vertUV;
    gl_Position = Projection * View * World * vec4(vertPosition, 1.0);
}

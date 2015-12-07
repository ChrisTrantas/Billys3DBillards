#version 440

in vec2 vertPosition;
in vec2 vertUV;

out vec2 fragUV;

uniform mat4 World;
uniform mat4 Projection;

void main()
{
    fragUV = vertUV;
    gl_Position = Projection * World * vec4(vertPosition, 0.0, 1.0);
}

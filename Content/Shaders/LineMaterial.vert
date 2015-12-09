#version 440

in vec2 vertPosition;

out vec2 fragUV;

uniform mat4 World;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * World * vec4(vertPosition, 0.0, 1.0);
}

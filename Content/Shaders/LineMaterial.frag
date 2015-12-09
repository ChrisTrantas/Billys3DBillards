#version 440

layout(location = 0) out vec4 fragColor;

uniform vec4 LineColor;

void main()
{
    fragColor = LineColor;
}

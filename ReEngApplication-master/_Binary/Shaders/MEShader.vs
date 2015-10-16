#version 330
in vec3 Position_b;
in vec3 UV_b;
in vec3 Normal_b;
in vec3 Binormal_b;
in vec3 Tangent_b;
in vec3 Color_b;

uniform mat4 MVP;
uniform mat4 m4ModelToWorld;
uniform vec3 CameraPosition;
uniform int nElements;
uniform mat4 m4ToWorld[250];

out vec3 Normal_W;
out vec3 Tangent_W;
out vec3 Binormal_W;
out vec3 Position_W;
out vec3 Eye_W;
out vec2 UV;
out vec3 Color;

void main()
{
	//gl_InstanceID
	if( nElements < 1 )
		gl_Position = MVP * vec4(Position_b, 1);
	else
		gl_Position = (MVP * m4ToWorld[gl_InstanceID]) * vec4(Position_b, 1);
	
	UV = UV_b.xy;
	Color = Color_b;

	Position_W =	(m4ModelToWorld * vec4(Position_b,1)).xyz;
	Normal_W =		(m4ModelToWorld * vec4(Normal_b,0)).xyz;
	Tangent_W =		(m4ModelToWorld * vec4(Tangent_b, 0.0)).xyz;
	Binormal_W =	(m4ModelToWorld * vec4(Binormal_b, 0.0)).xyz;
	Eye_W = CameraPosition;
}
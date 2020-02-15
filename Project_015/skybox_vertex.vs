#version 400 core

layout(location = 0) in vec3 inPos;

out vec3 TexCoord;

uniform mat4 View;
uniform mat4 Projection;

void main()
{
	TexCoord = inPos;
	vec4 Pos = Projection * View * vec4(inPos, 1.0f);
	gl_Position = Pos.xyww;
}
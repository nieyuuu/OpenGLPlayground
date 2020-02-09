#version 400 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

uniform mat4 TranslateMat;

void main()
{
	gl_Position = TranslateMat * vec4(inPos, 1.0f);
	TexCoord = inTexCoord;
}
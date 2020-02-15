#version 400 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

uniform mat4 Model;
uniform mat4 LightSpaceMatrix;

void main()
{
	gl_Position = LightSpaceMatrix * Model * vec4(inPos, 1.0f);
}
#version 400 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 wsPos;
out vec3 wsNormal;

void main()
{
	wsPos = (Model * vec4(inPos, 1.0f)).xyz;
	wsNormal = mat3(transpose(inverse(Model))) * inNormal;
	gl_Position = Projection * View * Model * vec4(inPos, 1.0f);
}
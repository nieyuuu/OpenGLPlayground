#version 400 core

layout(location = 0) in vec3 inPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(inPos, 1.0f);
}
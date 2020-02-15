#version 400 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out VS_OUT
{
	vec3 wsFragPos;
	vec3 wsNormal;
	vec2 TexCoord;
	vec4 LightSpaceFragPos;
} vs_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 LightSpaceMatrix;

void main()
{
	vs_out.wsFragPos = (Model * vec4(inPos, 1.0f)).xyz;
	vs_out.wsNormal = mat3(transpose(inverse(Model))) * inNormal;
	vs_out.TexCoord = inTexCoord;
	vs_out.LightSpaceFragPos = LightSpaceMatrix * Model * vec4(inPos, 1.0f);

	gl_Position = Projection * View * Model * vec4(inPos, 1.0f);
}
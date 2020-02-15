#version 400 core

in vec3 wsPos;
in vec3 wsNormal;

out vec4 FragColor;

uniform samplerCube Skybox;
uniform vec3 wsCameraPos;

void main()
{
	vec3 ViewDir = normalize(wsPos - wsCameraPos);
	vec3 Reflection = reflect(ViewDir, normalize(wsNormal));
	FragColor = texture(Skybox, Reflection);
}
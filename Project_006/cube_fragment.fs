#version 400 core

out vec4 FragColor;

in vec3 wsPos;
in vec3 wsNormal;

uniform vec3 ObjectColor;
uniform float Shiness;

uniform vec3 LightColor;
uniform vec3 wsLightPos;

uniform vec3 wsCameraPos;

void main()
{
	float AmbientStrength = 0.1f;

	vec3 LightDir = normalize(wsLightPos - wsPos);
	float Diffuse = max(dot(LightDir, normalize(wsNormal)), 0.0f);

	float SpecularStrength = 0.5f;
	vec3 ViewDir = normalize(wsCameraPos - wsPos);
	vec3 ReflectDir = normalize(reflect(-LightDir, wsNormal));
	float Specular = SpecularStrength * pow(max(dot(ViewDir, ReflectDir), 0.0f), Shiness);

	vec3 Result = (AmbientStrength + Diffuse + Specular) * LightColor * ObjectColor;
	FragColor = vec4(Result, 1.0f);
}
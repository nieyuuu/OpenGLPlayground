#version 400 core

out vec4 FragColor;

in vec3 wsPos;
in vec3 wsNormal;
in vec2 TexCoord;

struct Material
{
	sampler2D Diffuse;
	sampler2D Specular;
	float Shiness;
};

struct Light
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float Constant;
	float Linear;
	float Quadratic;

	vec3 wsPos;
};

uniform Material m;
uniform Light l;
uniform vec3 wsCameraPos;

void main()
{
	float Distance = length(l.wsPos - wsPos);
	float Attenuation = 1.0f / (l.Constant + l.Linear * Distance + l.Quadratic * pow(Distance, 2.0f));

	vec3 Ambient = Attenuation * l.Ambient * texture(m.Diffuse, TexCoord).rgb;

	vec3 LightDir = normalize(l.wsPos - wsPos);
	float Diff = max(dot(LightDir, normalize(wsNormal)), 0.0f);
	vec3 Diffuse = Attenuation * Diff * l.Diffuse * texture(m.Diffuse, TexCoord).rgb;

	vec3 ViewDir = normalize(wsCameraPos - wsPos);
	vec3 Reflection = reflect(-LightDir, normalize(wsNormal));
	float Spec = pow(max(dot(ViewDir, Reflection), 0.0f), m.Shiness);
	vec3 Specular = Attenuation * Spec * l.Specular * texture(m.Specular, TexCoord).rgb;

	FragColor = vec4(Ambient + Diffuse + Specular, 1.0f);
}
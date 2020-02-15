#version 400 core

in VS_OUT
{
	vec3 wsFragPos;
	vec3 wsNormal;
	vec2 TexCoord;
	vec4 LightSpaceFragPos;
} fs_in;

out vec4 FragColor;

uniform float Shiness;
uniform vec3 LightColor;
uniform vec3 wsLightPos;
uniform vec3 wsCameraPos;

uniform sampler2D Texture;
uniform sampler2D DepthMap;

float calculateShadow(bool tese)
{
	vec3 ProjectionCoord = fs_in.LightSpaceFragPos.xyz / fs_in.LightSpaceFragPos.w;
	ProjectionCoord = ProjectionCoord * 0.5f + 0.5f;

	float CurrentDepth = ProjectionCoord.z;

	//depth bias
	vec3 Normal = normalize(fs_in.wsNormal);
	vec3 LightDir = normalize(wsLightPos - fs_in.wsFragPos);
	float Bias = max(0.05 * (1.0 - dot(Normal, LightDir)), 0.005);

	//PCF
	float Shadow = 0.0f;
	vec2 TexelSize = 1.0f / textureSize(DepthMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float PCFDepth = texture(DepthMap, ProjectionCoord.xy + vec2(x, y) * TexelSize).r;
			Shadow += CurrentDepth - Bias > PCFDepth ? 1.0f : 0.0f;
		}
	}

	Shadow /= 9.0f;

	if(ProjectionCoord.z > 1.0f)
		Shadow = 0.0f;

	return Shadow;
}

void main()
{
	float Shadow = calculateShadow(false);

	vec3 Color = texture(Texture, fs_in.TexCoord).xyz;

	vec3 Ambient = 0.3f * Color;

	vec3 LightDir = normalize(wsLightPos - fs_in.wsFragPos);
	float Diff = max(dot(LightDir, normalize(fs_in.wsNormal)), 0.0f);
	vec3 Diffuse = Diff * LightColor * Color;

	vec3 ViewDir = normalize(wsCameraPos - fs_in.wsFragPos);
	vec3 Reflection = reflect(-LightDir, normalize(fs_in.wsNormal));
	vec3 HalfVector = normalize(LightDir + ViewDir);
	float Spec = pow(max(dot(normalize(fs_in.wsNormal), HalfVector), 0.0f), Shiness);
	vec3 Specular = Spec * LightColor * Color;

	vec3 Lighting = Ambient + (1.0f - Shadow) * (Diffuse + Specular);

	FragColor = vec4(Lighting, 1.0f);
}
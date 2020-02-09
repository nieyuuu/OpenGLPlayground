#version 400 core

out vec4 FragColor;

uniform float Near;
uniform float Far;

float linearizeDepth(float Depth)
{
	float NDC = Depth * 2.0f - 1.0f;
	return (2.0f * Near * Far) / (Far + Near - NDC * (Far - Near));
}

void main()
{
	//linear depth
	float LinearDepth = linearizeDepth(gl_FragCoord.z) / Far;
	FragColor = vec4(vec3(LinearDepth), 1.0f);

	//nonlinear depth
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0f);
}
#version 400 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	//FragColor = texture(Texture, TexCoord);
	FragColor = vec4(vec3(1.0 - texture(Texture, TexCoord)), 1.0);
}
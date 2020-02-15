#version 400 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	//FragColor = texture(Texture, TexCoord);

	FragColor = texture(Texture, TexCoord);
	float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    FragColor = vec4(average, average, average, 1.0);

	//FragColor = vec4(vec3(1.0 - texture(Texture, TexCoord)), 1.0);
}
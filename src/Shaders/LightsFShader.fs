#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 lightColour;

uniform sampler2D texture_diffuse1;

void main()
{
	FragColor = texture(texture_diffuse1, TexCoords) * vec4(lightColour, 1.0);
}
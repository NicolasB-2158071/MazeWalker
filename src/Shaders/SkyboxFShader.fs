#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

// texture samplers
uniform samplerCube textureOne;

void main()
{
	FragColor = texture(textureOne, TexCoord);
}
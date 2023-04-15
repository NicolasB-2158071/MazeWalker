#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

// texture samplers
uniform samplerCube textureOne;

void main()
{
	FragColor = texture(textureOne, TexCoord) * vec4(0.2f, 0.3f, 0.4f, 1.0f);
}
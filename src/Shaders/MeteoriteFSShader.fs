#version 330 core
struct Material {
	sampler2D texture_diffuse1;
	vec3 specular; // Don't use these ones
	float shininess;
};

out vec4 FragColor;

in vec2 TexCoords;

uniform Material material;

void main()
{
	FragColor = texture(material.texture_diffuse1, TexCoords);
}
#version 330 core
struct Material {
	sampler2D texture_diffuse1;
	vec3 specular;
	float shininess;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 lightColour;

uniform Material material;


void main()
{
	FragColor = texture(material.texture_diffuse1, TexCoords) * vec4(lightColour, 1.0);
}
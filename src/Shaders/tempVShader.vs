#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 instancingModel;

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float Kc;
	float K1;
	float Kq;
};

#define NUMBER_OF_LIGHTS 8

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

layout (std140) uniform PointLightBlock
{
	PointLight pointLights[NUMBER_OF_LIGHTS];
};

out vec3 lightColour;

uniform mat4 model;

void main()
{
	gl_Position = projection * view * instancingModel * vec4(aPos, 1.0f);
	lightColour = pointLights[gl_InstanceID].ambient;
}
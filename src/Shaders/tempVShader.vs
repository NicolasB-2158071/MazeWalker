#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in mat4 instancingModel;

uniform mat4 model;

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
	gl_Position = projection * view * instancingModel * vec4(aPos, 1.0f);
}
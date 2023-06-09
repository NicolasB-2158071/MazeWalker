#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 6) in mat4 instancingModel; // Bitangent and tangent, other stuff takes 2 - 5 in

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * instancingModel * vec4(aPos, 1.0f);
	TexCoords = aTexCoords;
}
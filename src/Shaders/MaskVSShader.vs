#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 6) in mat4 instancingModel;
layout (location = 10) in mat3 normalModel;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
    gl_Position = projection * view * instancingModel * vec4(aPos, 1.0f);
	TexCoords = aTexCoords;

	Normal = normalModel * aNormal;
	FragPos = vec3(view * instancingModel * vec4(aPos, 1.0f));
}
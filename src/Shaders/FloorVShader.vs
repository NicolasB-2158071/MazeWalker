#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
uniform mat3 normalModel;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;

	Normal = normalModel * aNormal;
	FragPos = vec3(view * model * vec4(aPos, 1.0f));
}
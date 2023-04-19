#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoord;

layout (std140) uniform TransformationBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
	mat4 noTranslation = mat4(mat3(view));
	vec4 tempPos = projection * noTranslation * vec4(aPos, 1.0); // No model matrix needed
	gl_Position = tempPos.xyww; // z == w == 1.0 (farthest away for depth test)
	TexCoord = aPos; // Direction == pos (because (0, 0, 0))
}
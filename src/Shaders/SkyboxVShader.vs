#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 tempPos = projection * view * vec4(aPos, 1.0); // No model matrix needed
	gl_Position = tempPos.xyww; // z == w == 1.0 (farthest away for depth test)
	TexCoord = aPos; // Direction == pos (because (0, 0, 0))
}
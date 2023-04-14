#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aOffset; // Instancing offset

out vec2 TexCoord;

uniform mat4 model; // Floor, walls scaling
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 newPos = model * vec4(aPos, 1.0f);
	gl_Position = projection * view * vec4(newPos.x + aOffset.x, newPos.y, newPos.z + aOffset.y, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
#version 330 core
out vec4 FragColor;

uniform float time;

void main()
{   
	float colour = (sin(time) + 1.0) / 2;
	FragColor = vec4(colour, colour, colour, 1.0);
}
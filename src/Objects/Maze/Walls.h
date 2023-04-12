#pragma once

#include "../../Renderer/Renderer.h"

class Walls
{
public:
	Walls(); // Via instancing meerdere kunnen tekenen (later offsets)
	void draw(Renderer& renderer);

private:
	VertexArray m_vao;
	Texture m_texture;
	// locaties
	// Instance 

	void initVAO();
};
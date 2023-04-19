#pragma once

#include "../../Renderer/Renderer.h"

class Walls
{
public:
	Walls();

	void draw(Renderer& renderer);

	// setLocations and amount
	void initObject(int amount, glm::mat4* locations);

private:
	VertexArray m_vao;
	Texture m_texture;
	Shader m_shader;

	int m_amount = 1;
};
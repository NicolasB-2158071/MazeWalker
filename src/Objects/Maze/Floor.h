#pragma once


#include "../../Buffers/VertexArray.h"
#include "../../Textures/Texture.h"
#include "../../Renderer/Renderer.h"

class Floor
{
public:
	Floor(const glm::vec2& floorSize);

	void draw(Renderer& renderer);


private:
	VertexArray m_vao;
	glm::vec2 m_floorSize;
	Texture m_texture;

	void initVAO();
};
#pragma once

#include "../../Renderer/Renderer.h"

class Walls
{
public:
	Walls(const glm::vec3& wallSize, int amount, glm::vec2* locations);

	void draw(Renderer& renderer);

	// setLocations and amount

private:
	const int m_amount;
	glm::vec2* m_locations;
	glm::vec3 m_wallSize;

	glm::vec2 temp[2];

	VertexArray m_vao;
	Texture m_texture;

	void initVAO();
};
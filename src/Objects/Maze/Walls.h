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


	VertexArray m_vao;
	Texture m_texture;

	void initVAO();
};
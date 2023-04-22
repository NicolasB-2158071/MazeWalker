#pragma once

#include "../../Renderer/Renderer.h"

class Walls
{
public:
	Walls();

	void draw(Renderer& renderer);

	// setLocations and amount
	void initObject(int amount, std::vector<glm::mat4>& locations);

private:
	VertexArray m_vao;
	Texture m_texture;
	Shader m_shader;

	int m_amount = 1;

	void initLighting();
	std::vector<glm::mat3> calculateNormalModels(const std::vector<glm::mat4>& locations) const;
};
#pragma once

#include "../Model.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

class Meteorite
{
public:
	Meteorite();

	void draw(Renderer& renderer);
	void initObject(float mazeWidth, float mazeHeight);

	const static unsigned int NUMBER_OF_METEORITES = 5;

private:
	Model m_meteoriteModel;
	Shader m_shader;
	VertexBuffer m_ivbo;

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;

	void calculateLocations(float mazeWidth, float mazeHeight);
	void initMatrices();
};
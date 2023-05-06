#include "Meteorite.h"

#include "../../Util/RandomGenerator.h"

Meteorite::Meteorite() : m_shader{"src/Shaders/MeteoriteVSShader.vs", "src/Shaders/MeteoriteFSShader.fs" }
{
	m_shader.use();
	m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
}

void Meteorite::draw(Renderer& renderer)
{
	renderer.drawMeteorites(m_meteoriteModel, m_shader, NUMBER_OF_METEORITES);
}

void Meteorite::calculateLocations(float mazeWidth, float mazeHeight)
{
	for (int i = 0; i < NUMBER_OF_METEORITES; ++i)
		m_locations.push_back(glm::vec2
		{
			RandomGenerator::randomFloat(0.0f, mazeWidth),
			RandomGenerator::randomFloat(0.0f, mazeHeight),
		});
}

void Meteorite::initMatrices()
{
	for (auto& location : m_locations)
	{
		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ location.x, RandomGenerator::randomFloat(8.0f, 30.0f), location.y});
		model = glm::rotate(model, glm::radians(RandomGenerator::randomFloat(8.0f, 30.0f)), glm::vec3{ 0.0f, 1.0f, 0.0f });
		model = glm::scale(model, glm::vec3{ 1.0f, 1.0f, 1.0f });
		m_locationsMatrices.push_back(std::move(model));
	}
}

void Meteorite::initObject(float mazeWidth, float mazeHeight)
{
	calculateLocations(mazeWidth, mazeHeight);
	initMatrices();
	m_ivbo.setData(m_locationsMatrices.data(), sizeof(glm::mat4) * NUMBER_OF_METEORITES);
	m_meteoriteModel = Model{ "res/Models/meteorite/Meteorite.obj", false, &m_ivbo };
}

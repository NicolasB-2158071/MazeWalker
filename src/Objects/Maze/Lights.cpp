#include "Lights.h"

#include <random>

Lights::Lights() : m_lightBuffer{ 80 * NUMBER_OF_LIGHTS, POINTLIGHT_BLOCK}
{
	initPointLights();
}
// 64 - ben size aan het wasten
void Lights::initPointLights()
{
	srand(time(0));
	m_lightBuffer.bind();
	unsigned int offset{};
	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
	{
		PointLight pl{};
		pl.position = glm::vec3{ locations[i].x, 0.5f, locations[i].y };
		pl.ambient = glm::vec3{ glm::vec3{ 0.8f + randomFloat() / 3, 0.8f + randomFloat() / 3, 0.8f + randomFloat() / 3}}; // Colour
		pl.diffuse = glm::vec3{ glm::vec3{ randomFloat(), randomFloat(), randomFloat() } };
		pl.specular = glm::vec3{ glm::vec3{ randomFloat(), randomFloat(), randomFloat()} };
		pl.Kc = 1.0f;
		pl.K1 = 0.09f;
		pl.Kq = 0.032f;

		m_lightBuffer.addData(offset, 16, &pl.position);
		m_lightBuffer.addData((offset += 16), 16, &pl.ambient);
		m_lightBuffer.addData((offset += 16), 16, &pl.diffuse);
		m_lightBuffer.addData((offset += 16), 16, &pl.specular);
		m_lightBuffer.addData((offset += 16), 4, &pl.Kc);
		m_lightBuffer.addData((offset += 4), 4, &pl.K1);
		m_lightBuffer.addData((offset += 4), 4, &pl.Kq);
		offset += 8; // Offset 4 struct of array (and 4 of float above)
	}
}

// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
float Lights::randomFloat() const
{
	return (float)(rand()) / (float)(RAND_MAX);
}
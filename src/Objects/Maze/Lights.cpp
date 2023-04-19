#include "Lights.h"

#include <random>

Lights::Lights() : /*m_lightBuffer{sizeof(PointLight) * NUMBER_OF_LIGHTS, POINTLIGHT_BLOCK},*/ m_lightBuffer{ 64, POINTLIGHT_BLOCK}
{
	initPointLights();
}
// 64 - ben size aan het wasten
void Lights::initPointLights()
{
	srand(time(0));
	unsigned int offset = 0;
	m_lightBuffer.bind();
	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
	{
		PointLight pl{};
		pl.position = glm::vec3{ locations[i].x, 0.5f, locations[i].y };
		pl.ambient = glm::vec3{ randomFloat(), randomFloat(), randomFloat() };
		pl.diffuse = glm::vec3{ randomFloat(), randomFloat(), randomFloat() };
		pl.specular = glm::vec3{ randomFloat(), randomFloat(), randomFloat() };
		pl.Kc = 1.0f;
		pl.K1 = 0.09f;
		pl.Kq = 0.032f;

		m_lightBuffer.addData(offset, 64, &pl);
		offset += sizeof(PointLight);
	}

}

// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
float Lights::randomFloat() const
{
	return (float)(rand()) / (float)(RAND_MAX);
}


//m_shader.setVec3("light.position", glm::vec3{ 1.0f, 1.0f, 1.0f });
//m_shader.setVec3("light.ambient", glm::vec3{ 0.8f, 0.8f, 0.8f });
//m_shader.setVec3("light.diffuse", glm::vec3{ 0.5f, 0.5f, 0.5f });
//m_shader.setVec3("light.specular", glm::vec3{ 1.0f, 1.0f, 1.0f });
//m_shader.setFloat("light.Kc", 1.0f);
//m_shader.setFloat("light.K1", 0.09f);
//m_shader.setFloat("light.Kq", 0.032f);
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Buffers/UniformBuffer.h"

class Lights
{
public:

	struct PointLight
	{
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float Kc;
		float K1;
		float Kq;
	};

	const static unsigned int POINTLIGHT_BLOCK = 1;
	const static unsigned int NUMBER_OF_LIGHTS = 2;

	Lights();

	//void draw(Renderer& renderer);

	// Gegeven point light locaties (mazebuilder) -> set point lights (met random waardes)
	// tekent ook via instancing de punten (via model)

private:
	UniformBuffer m_lightBuffer;

	glm::vec2 locations[NUMBER_OF_LIGHTS] = {
		glm::vec2{1.0f, 1.0f},
		glm::vec2{10.0f, 10.0f}
	};

	void initPointLights();
	float randomFloat() const;
};
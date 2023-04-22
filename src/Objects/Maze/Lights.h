#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "../../Renderer/Renderer.h"
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
	const static unsigned int NUMBER_OF_LIGHTS = 8;

	Lights();
	void setLocations(const std::vector<glm::vec2>& locations);

	void draw(Renderer& renderer);

	// Gegeven point light locaties (mazebuilder) -> set point lights (met random waardes)
	// tekent ook via instancing de punten (via model)

private:
	UniformBuffer m_lightBuffer;
	VertexArray m_vao;
	Shader m_shader;

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;

	void initPointLights();
	void initObject();
	void initMatrices();

	float randomFloat() const;
};
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Audio.hpp>
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
	const static unsigned int NUMBER_OF_LIGHTS = 10;

	Lights();

	void setLocations(const std::vector<glm::vec2>& locations);
	void draw(Renderer& renderer);
	void initLightsInput(EventManager* eventManager);

private:
	UniformBuffer m_lightBuffer;
	VertexArray m_vao;
	Shader m_shader;
	void initObject();

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;
	void initMatrices();

	glm::vec3 m_lightColours[NUMBER_OF_LIGHTS];
	bool m_lightsOn[NUMBER_OF_LIGHTS];
	void setLightColour(int pointLightNumber, const glm::vec3& colour);
	void initPointLights();

	sf::Sound m_chimeSound;
	sf::SoundBuffer m_buffer;
	void initAudio();

	void handleRightClickPicking();
	void handleLeftClickPicking();

	// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
	float randomFloat() const;
};
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
	const static unsigned int NUMBER_OF_LIGHTS = 8;

	Lights();
	void setLocations(const std::vector<glm::vec2>& locations);
	void setCamera(Camera* camera);

	void draw(Renderer& renderer);

	void initLightsInput(EventManager* eventManager);

private:
	UniformBuffer m_lightBuffer;
	VertexArray m_vao;
	Shader m_shader;

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;

	sf::Sound m_chimeSound;
	sf::SoundBuffer buffer;

	Camera* m_camera = nullptr;

	void handleRay(const glm::vec3& ray); // checkt op collision + doet aanpassing

	void setRandomLightColour(int pointLightNumber);

	void initAudio();
	void initPointLights();
	void initObject();
	void initMatrices();

	float randomFloat() const;
};
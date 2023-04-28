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

	glm::vec3 m_lightColours[NUMBER_OF_LIGHTS];
	bool m_lightsOn[NUMBER_OF_LIGHTS] = { true };

	//sf::Sound m_chimeSound;
	//sf::SoundBuffer m_buffer;

	Camera* m_camera = nullptr;

	// https://antongerdelan.net/opengl/images/raysphere.png simpel sphere collision (better would be AABB)
	void handleRightClickPicking(double mouseX, double mouseY);
	void handleLeftClickPicking(double mouseX, double mouseY);

	bool isPickingCollision(const glm::vec3& ray, const glm::vec3& origin, const glm::vec3& center) const;

	void setLightColour(int pointLightNumber, const glm::vec3& colour);

	void initAudio();
	void initPointLights();
	void initObject();
	void initMatrices();

	// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
	float randomFloat() const;
};
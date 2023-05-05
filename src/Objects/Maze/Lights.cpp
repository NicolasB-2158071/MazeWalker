#include "Lights.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"

#include "../../Camera/InteractionHandler.h"

#include <random>

Lights::Lights() : m_lightBuffer{ 80 * NUMBER_OF_LIGHTS, POINTLIGHT_BLOCK }, m_shader{ "src/Shaders/LightsVShader.vs", "src/Shaders/LightsFShader.fs" }
{
	std::fill_n(m_lightsOn, NUMBER_OF_LIGHTS, true);
	srand(time(0));
	m_shader.use();
	m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
	m_shader.bindUniformBlock("PointLightBlock", POINTLIGHT_BLOCK);
	initAudio();
}

void Lights::setLocations(const std::vector<glm::vec2>& locations)
{
	m_locations = locations;
	initPointLights();
	initObject();
}

void Lights::draw(Renderer& renderer)
{
	renderer.drawLights(m_lightModel, m_shader, NUMBER_OF_LIGHTS);
}

void Lights::initLightsInput(EventManager* eventManager)
{
	eventManager->registerCallback(EventType::MOUSE_LEFT_CLICK, [this](EventInfo& info)
	{
		MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
		handleLeftClickPicking(); // Always from center for clicking
	});
	eventManager->registerCallback(EventType::MOUSE_RIGHT_CLICK, [this](EventInfo& info)
	{
		handleRightClickPicking(); // Always from center for clicking
	});
}

void Lights::initPointLights()
{
	m_lightBuffer.bind();
	unsigned int offset{};
	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
	{
		PointLight pl{};
		pl.position = glm::vec3{ m_locations[i].x, 0.5f, m_locations[i].y };
		//pl.ambient = glm::vec3{ glm::vec3{ 0.8f /* + randomFloat() / 3*/, 0.8f /* + randomFloat() / 3*/, 0.8f /* + randomFloat() / 3*/}}; // Colour
		pl.ambient = glm::vec3{  glm::vec3{ 0.3 + randomFloat(), 0.3 + randomFloat(), 0.3 + randomFloat() } }; // Colour
		pl.diffuse = glm::vec3{ glm::vec3{ randomFloat(), randomFloat(), randomFloat() } };
		pl.specular = glm::vec3{ glm::vec3{ randomFloat(), randomFloat(), randomFloat()} };
		pl.Kc = 1.0f;
		pl.K1 = 0.09f;
		pl.Kq = 0.032f;

		m_lightColours[i] = pl.ambient;

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

void Lights::initObject()
{
	initMatrices();
	m_ivbo.setData(m_locationsMatrices.data(), sizeof(glm::mat4) * NUMBER_OF_LIGHTS);
	m_lightModel = Model{"res/Models/torch/torch.fbx", false, &m_ivbo };
}

void Lights::initMatrices()
{
	for (auto& location : m_locations)
	{
		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ location.x, 1.0f, location.y });
		model = glm::scale(model, glm::vec3{ 0.01f, 0.005f, 0.01f });
		m_locationsMatrices.push_back(std::move(model));
	}
}

void Lights::initAudio()
{
	if (!m_buffer.loadFromFile("res/Audio/LightsOnOff.wav"))
	{
		std::cout << "ERROR loading light sound";
		return;
	}
	m_chimeSound.setBuffer(m_buffer);
	m_chimeSound.setMinDistance(3.0f);
	m_chimeSound.setAttenuation(10.0f);
	m_chimeSound.setVolume(25.0f);
}

void Lights::setLightColour(int pointLightNumber, const glm::vec3& colour)
{
	m_lightBuffer.bind();
	m_lightBuffer.addData(80 * pointLightNumber + 16, 16, &colour);
}

void Lights::handleLeftClickPicking()
{
	InteractionHandler* ih{ InteractionHandler::getInstance() };
	glm::vec3 ray{ ih->calculateRayVectorFromCenter()};

	// Check for all lights if there is a collision
	int lightNumber{};
	for (auto& location : m_locations)
	{
		glm::vec3 center{ location.x + 0.05f, 1.0f, location.y + 0.05f }; // lightSize = 1.0f
		if (ih->isSphereRayCollisionFromCamera(ray, center, 0.1f, 8.0f))
		{
			m_chimeSound.setPosition(center.x, center.y, center.z);
			m_chimeSound.stop(); // Rewind
			m_chimeSound.play();
			setLightColour(lightNumber, m_lightsOn[lightNumber] ? glm::vec3{ 0.0f, 0.0f, 0.0f } : m_lightColours[lightNumber]); // Off/On
			m_lightsOn[lightNumber] = !m_lightsOn[lightNumber];
		}
		++lightNumber;
	}
}

void Lights::handleRightClickPicking()
{
	InteractionHandler* ih{ InteractionHandler::getInstance() };
	glm::vec3 ray{ ih->calculateRayVectorFromCenter() };

	// Check for all lights if there is a collision
	int lightNumber{};
	for (auto& location : m_locations)
	{
		glm::vec3 center{ location.x + 0.05f, 1.0f, location.y + 0.05f }; // lightSize = 1.0f
		if (ih->isSphereRayCollisionFromCamera(ray, center, 0.1f, 8.0f))
		{
			m_lightColours[lightNumber] = glm::vec3{ 0.3 + randomFloat(), 0.3 + randomFloat(), 0.3 + randomFloat() };
			if (m_lightsOn[lightNumber])
				setLightColour(lightNumber, m_lightColours[lightNumber]);
		}
		++lightNumber;
	}
}

float Lights::randomFloat() const
{
	return (float)(rand()) / (float)(RAND_MAX);
}
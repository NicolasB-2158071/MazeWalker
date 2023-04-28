#include "Lights.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"

#include <random>

Lights::Lights() : m_lightBuffer{ 80 * NUMBER_OF_LIGHTS, POINTLIGHT_BLOCK }, m_shader{ "src/Shaders/tempVShader.vs", "src/Shaders/tempFShader.fs" }
{
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

void Lights::setCamera(Camera* camera)
{
	m_camera = camera;
}

void Lights::draw(Renderer& renderer)
{
	renderer.drawLights(m_vao, m_shader, NUMBER_OF_LIGHTS);
}

void Lights::initLightsInput(EventManager* eventManager)
{
	eventManager->registerCallback(EventType::MOUSE_LEFT_CLICK, [this](EventInfo& info)
	{
		MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
		handleLeftClickPicking(mouseInfo.xpos, mouseInfo.ypos);
	});
	eventManager->registerCallback(EventType::MOUSE_RIGHT_CLICK, [this](EventInfo& info)
	{
		MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
		handleRightClickPicking(mouseInfo.xpos, mouseInfo.ypos);
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
    // LBB (0) - LBT (1) - RBB (2) - RBT (3)
    // LFB (4) - LFT (5) - RFB (6) - RFT (7)
	float vertices[] = {
		// Pos
		0.0f,  0.0f,  0.0f,
	    0.0f,  1.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  1.0f,  0.0f,

	    0.0f,  0.0f,  1.0f,
	    0.0f,  1.0f,  1.0f,
		1.0f,  0.0f,  1.0f,
		1.0f,  1.0f,  1.0f
	};

    unsigned int indices[] = {
        0, 1, 2, 1, 3, 2, // Behind (LBB - LBT - RBB - LBT - RBT - RBB)
        4, 5, 6, 5, 7, 6, // Front (LFB - LFT - RFB - LFT - RFT - RFB)
        4, 0, 5, 1, 5, 0, // Left (LFB - LBB - LFT - LBT - LFT - LBB)
        6, 2, 7, 3, 7, 2, // Right (RFB - RBB - RFT - RBT - RFT - RBB)
        4, 6, 0, 0, 6, 2, // Bottom (LFB - RFB - LBB - LBB - RFB - RBB)
        5, 7, 1, 1, 7, 3 // Top (LFT - RFT - LBT - LBT - RFT - RBT)
    };

    VertexBuffer vbo{ vertices, sizeof(vertices) };
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

    // bind
    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
	VertexBuffer ivbo{ m_locationsMatrices.data(), sizeof(glm::mat4) * NUMBER_OF_LIGHTS};

	m_vao.connectInstanceBuffer(ivbo, BufferAttribute{ 4, GL_FLOAT, GL_FALSE }, 1, 4, sizeof(glm::vec4));
    m_vao.unbind();
}

// Best in mazebuilder
void Lights::initMatrices()
{
	for (auto& location : m_locations)
	{
		glm::mat4 model{ 1.0f };
		model = glm::translate(model, glm::vec3{ location.x, 1.0f, location.y });
		model = glm::scale(model, glm::vec3{ 0.1f, 0.1f, 0.1f });
		m_locationsMatrices.push_back(std::move(model));
	}
}

void Lights::initAudio()
{
	//if (!m_buffer.loadFromFile("res/Audio/newTest.wav"))
	//{
	//	std::cout << "ERROR loading light sound";
	//	return;
	//}
	//m_chimeSound.setBuffer(m_buffer);
	//m_chimeSound.setRelativeToListener(true);
	//m_chimeSound.setMinDistance(3.0f);
	//m_chimeSound.setAttenuation(30.0f);
}

bool Lights::isPickingCollision(const glm::vec3& ray, const glm::vec3& origin, const glm::vec3& center) const
{
	float radius{ 0.1f }; // hardcoded
	float b{ glm::dot(ray, origin - center) };
	float c{ glm::dot((origin - center), (origin - center)) - radius * radius };

	// Check collision
	float length{ glm::length(center - origin) }; // Max range
	if (length < 3.0f && b * b - c >= 0)
		return true;
	return false;
}

void Lights::setLightColour(int pointLightNumber, const glm::vec3& colour)
{
	m_lightBuffer.bind();
	m_lightBuffer.addData(80 * pointLightNumber + 16, 16, &colour);
}

void Lights::handleLeftClickPicking(double mouseX, double mouseY)
{
	glm::vec3 ray{ m_camera->calculateRayVector(mouseX, mouseY) };
	glm::vec3 origin{ m_camera->getCameraPos() };
	int lightNumber{};

	// Check for all lights if there is a collision
	for (auto& location : m_locations)
	{
		glm::vec3 center{ location.x + 0.05f, 1.0f, location.y + 0.05f }; // lightSize = 1.0f
		if (isPickingCollision(ray, origin, center))
		{
			//m_chimeSound.setPosition(center.x, center.y, center.z);
			//m_chimeSound.stop(); // Rewind
			//m_chimeSound.play();
			setLightColour(lightNumber, m_lightsOn[lightNumber] ? m_lightColours[lightNumber] : glm::vec3{0.0f, 0.0f, 0.0f}); // Off/On
			m_lightsOn[lightNumber] = !m_lightsOn[lightNumber];
		}
		++lightNumber;
	}
}

void Lights::handleRightClickPicking(double mouseX, double mouseY)
{
	glm::vec3 ray{ m_camera->calculateRayVector(mouseX, mouseY) };
	glm::vec3 origin{ m_camera->getCameraPos() };
	int lightNumber{};

	// Check for all lights if there is a collision
	for (auto& location : m_locations)
	{
		glm::vec3 center{ location.x + 0.05f, 1.0f, location.y + 0.05f }; // lightSize = 1.0f
		if (isPickingCollision(ray, origin, center))
		{
			// Sound
			m_lightColours[lightNumber] = glm::vec3{ 0.3 + randomFloat(), 0.3 + randomFloat(), 0.3 + randomFloat() };
			if (!m_lightsOn[lightNumber])
				setLightColour(lightNumber, m_lightColours[lightNumber]);
		}
		++lightNumber;
	}
}

float Lights::randomFloat() const
{
	return (float)(rand()) / (float)(RAND_MAX);
}
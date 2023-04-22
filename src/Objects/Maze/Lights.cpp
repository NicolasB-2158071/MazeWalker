#include "Lights.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"

#include <random>

Lights::Lights() : m_lightBuffer{ 80 * NUMBER_OF_LIGHTS, POINTLIGHT_BLOCK }, m_shader{ "src/Shaders/tempVShader.vs", "src/Shaders/tempFShader.fs" }
{
	m_shader.use();
	m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
	m_shader.bindUniformBlock("PointLightBlock", POINTLIGHT_BLOCK);
}

void Lights::setLocations(const std::vector<glm::vec2>& locations)
{
	m_locations = locations;
	initPointLights();
	initObject();
}

void Lights::draw(Renderer& renderer)
{
	renderer.drawLights(m_vao, m_shader, NUMBER_OF_LIGHTS);
}

void Lights::initPointLights()
{
	srand(time(0));
	m_lightBuffer.bind();
	unsigned int offset{};
	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
	{
		PointLight pl{};
		pl.position = glm::vec3{ m_locations[i].x, 0.5f, m_locations[i].y };
		//pl.ambient = glm::vec3{ glm::vec3{ 0.8f /* + randomFloat() / 3*/, 0.8f /* + randomFloat() / 3*/, 0.8f /* + randomFloat() / 3*/}}; // Colour
		pl.ambient = glm::vec3{ glm::vec3{ 0.8f + randomFloat() / 3, 0.8f + randomFloat() / 3, 0.8f + randomFloat() / 3} }; // Colour
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

void Lights::initObject()
{
	initMatrices();
    // LBB (0) - LBT (1) - RBB (2) - RBT (3)
    // LFB (4) - LFT (5) - RFB (6) - RFT (7)
    float vertices[] = {
        // Pos
       -1.0f, -1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,

       -1.0f, -1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
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


// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
float Lights::randomFloat() const
{
	return (float)(rand()) / (float)(RAND_MAX);
}
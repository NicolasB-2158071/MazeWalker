#include "Walls.h"

#include "../../Buffers/VertexBuffer.h"
#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"


Walls::Walls(const glm::vec3& wallSize, int amount) : m_wallSize{ wallSize }, m_amount{ amount }, m_texture { "res/container.jpg", GL_RGB }
{
    m_locations[0] = glm::vec2{ 2.0f, 5.0f };
    m_locations[1] = glm::vec2{ -5.0f, -5.0f };
    m_locations[2] = glm::vec2{ 10.0f, -5.0f };
    m_locations[3] = glm::vec2{ -16.0f, 0.0f };
    m_locations[4] = glm::vec2{ 12.0f, -8.0f };

    initVAO();
}

void Walls::draw(Renderer& renderer)
{
    renderer.drawWalls(m_vao, m_wallSize, m_texture, m_amount);
}

void Walls::initVAO()
{
    // LBB (0) - LBT (1) - RBB (2) - RBT (3)
    // LFB (4) - LFT (5) - RFB (6) - RFT (7)
    float vertices[] = {
        // Pos              // Texture
       -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
       -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, -1.0f, 1.0f, 1.0f,

       -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
       -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
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
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);

    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
    VertexBuffer ivbo{ m_locations, sizeof(glm::vec2) * m_amount };
  
    m_vao.connectInstanceBuffer(ivbo, BufferAttribute{2, GL_FLOAT, GL_FALSE}, 2);
    m_vao.unbind();

    // Instancing buffer met met x, z offsets op basis van file
}

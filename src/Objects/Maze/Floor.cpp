#include "Floor.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"

Floor::Floor(const glm::vec2& size) : m_size{size}, m_texture{ "res/container.jpg", GL_RGB }
{
	initVAO();
}

void Floor::draw(Renderer& renderer)
{
    renderer.drawFloor(m_vao, m_size, m_texture);
}

void Floor::initVAO()
{
    float vertices[] = {
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
        1.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 0.0f, 1.0f, 0.0f, 1.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    VertexBuffer vbo{ vertices, sizeof(vertices) };
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);

    // bind
    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
    m_vao.unbind();
}

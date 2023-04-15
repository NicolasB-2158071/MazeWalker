#include "Floor.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"

Floor::Floor(const glm::mat4& projection) : m_texture{ "res/sandFloor.jpg", GL_RGB }, m_shader{"src/Shaders/FloorVShader.vs", "src/Shaders/FloorFShader.fs"}
{
    m_shader.use();
    m_shader.setMat4("projection", 1, GL_FALSE, projection);
    m_shader.setInt("textureOne", 0);
}

void Floor::draw(Renderer& renderer)
{
    renderer.drawFloor(m_vao, m_shader, m_texture);
}

// De model matrix ook geset worden
void Floor::initObject(float width, float height)
{
    m_shader.use();
    glm::mat4 model{ 1.0f };
    model = glm::translate(model, glm::vec3{(int)width, 0.0f, (int)height});
    m_shader.setMat4("model", 1, GL_FALSE, glm::scale(model, glm::vec3{ width, 0.0f, height}));

    float vertices[] = {
        // Pos            // Texture
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

#include "Floor.h"

#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "../../Buffers/VertexBuffer.h"
#include "Lights.h"

Floor::Floor() : m_texture{ "res/sandFloor.jpg" }, m_shader{"src/Shaders/FloorVShader.vs", "src/Shaders/FloorFShader.fs"}
{
    m_shader.use();
    m_shader.setInt("material.diffuse", 0);
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
    m_shader.bindUniformBlock("PointLightBlock", Lights::POINTLIGHT_BLOCK);
}

void Floor::draw(Renderer& renderer)
{
    renderer.drawFloor(m_vao, m_shader, m_texture);
}

void Floor::initObject(float width, float height)
{
    m_shader.use();
    glm::mat4 model{ 1.0f };
    model = glm::scale(model, glm::vec3{ width, 0.0f, height });
    glm::mat3 normalModel = glm::transpose(glm::inverse(model));
    m_shader.setMat4("model", 1, GL_FALSE, model);
    m_shader.setMat3("normalModel", 1, GL_FALSE, normalModel);

    initLighting();

    float vertices[] = {
        // Pos            // Texture   // Normals
        1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    VertexBuffer vbo{ vertices, sizeof(vertices) };
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

    // bind
    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
    m_vao.unbind();
}

void Floor::initLighting() const
{
    m_shader.setVec3("material.specular", glm::vec3{ 0.5f, 0.5f, 0.5f });
    m_shader.setFloat("material.shininess", 64.0f);
}

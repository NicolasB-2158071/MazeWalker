#include "Walls.h"

#include "../../Buffers/VertexBuffer.h"
#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"
#include "Lights.h"

Walls::Walls(const glm::vec3& wallSize) : m_texture{ "res/bookshelf.png" }, m_shader{ "src/Shaders/WallsVShader.vs", "src/Shaders/WallsFShader.fs" },
    m_wallSize{wallSize}
{
    m_shader.use();
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
    m_shader.bindUniformBlock("PointLightBlock", Lights::POINTLIGHT_BLOCK);
    initLighting();
}

void Walls::draw(Renderer& renderer)
{
    renderer.drawWalls(m_vao, m_shader, m_texture, m_amount);
}

void Walls::initObject(int amount, const std::vector<glm::vec2>& offsets)
{
    m_amount = amount;
    calculateXZLocations(offsets);
    initMatrices(offsets);

    m_shader.use();

    // Origin (0, 0, 0)
    float vertices[] = {
        // Top (LFT - LBT - RFT - RBT): pos, tex, normals (0 - 3)
         0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

         // Bottom (LFB - LBB - RFB - RBB): pos, tex, normals (4 - 7)
         0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

         // Front (LFB - LFT - RFB - RFT): pos, tex, normals (8 - 11)
         0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

         // Behind (LBB - LBT - RBB - RBT): pos, tex, normals (12 - 15)
         0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

         // Left (LFB - LBB - LFT - LBT): pos, tex, normals (16 - 19)
         0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

         // Right (RFB - RBB - RFT - RBT): pos, tex, normals (20 - 23)
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        12, 13, 14, 14, 15, 13, // Behind
        8, 9, 10, 10, 11, 9, // Front
        16, 17, 18, 18, 19, 17, // Left
        20, 21, 22, 22, 23, 21, // Right
        4, 5, 6, 6, 7, 5, // Bottom
        0, 1, 2, 2, 3, 1 // Top
    };

    VertexBuffer vbo{ vertices, sizeof(vertices) };
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
    VertexBuffer ivboLocation{ m_wallLocationMatrices.data(), sizeof(glm::mat4) * m_amount};
    VertexBuffer ivboNormalModel{ calculateNormalModels(m_wallLocationMatrices).data(), sizeof(glm::mat3) * m_amount };
  
    m_vao.connectInstanceBuffer(ivboLocation, BufferAttribute{4, GL_FLOAT, GL_FALSE}, 3, 6, sizeof(glm::vec4));
    m_vao.connectInstanceBuffer(ivboNormalModel, BufferAttribute{3, GL_FLOAT, GL_FALSE }, 7, 9, sizeof(glm::vec4));
    m_vao.unbind();
}

void Walls::calculateXZLocations(const std::vector<glm::vec2>& offsets)
{
    for (auto& offset : offsets)
        m_wallsXZLocations.push_back(glm::vec2{ offset.x * m_wallSize.x, offset.y * m_wallSize.z });
}

void Walls::initMatrices(const std::vector<glm::vec2>& offsets)
{
    for (auto& offset : offsets)
        m_wallLocationMatrices.push_back(calculateModel(offset.x, offset.y));
}

void Walls::initLighting()
{
    m_shader.setInt("material.diffuse", 0);
    m_shader.setVec3("material.specular", glm::vec3{ 0.8f, 0.8f, 0.8f });
    m_shader.setFloat("material.shininess", 64.0f);
}

glm::mat4 Walls::calculateModel(int xOffset, int zOffset) const
{
    glm::mat4 model{ 1.0f };
    model = glm::translate(model, glm::vec3{ m_wallSize.x * xOffset, 0, m_wallSize.z * zOffset });
    model = glm::scale(model, glm::vec3{ m_wallSize.x, m_wallSize.y, m_wallSize.z });

    return std::move(model);
}

std::vector<glm::mat3> Walls::calculateNormalModels(const std::vector<glm::mat4>& locations) const
{
    std::vector<glm::mat3> normalModels;
    for (const auto& location : locations)
    {
        glm::mat3 normalModel = glm::transpose(glm::inverse(location));
        normalModels.push_back(std::move(normalModel));
    }
    return normalModels;
}

bool Walls::isWallColision(const glm::vec2& cameraPos) const
{
    for (auto& pos : m_wallsXZLocations)
    {
        // Between x and z intervals (pos is origin of object)
        bool collisionX{ pos.x - OFFSET < cameraPos.x && cameraPos.x < pos.x + m_wallSize.x + OFFSET };
        bool collisionZ{ pos.y - OFFSET < cameraPos.y && cameraPos.y < pos.y + m_wallSize.z + OFFSET };
        if (collisionX && collisionZ)
            return true;
    }
    return false;
}

glm::vec3 Walls::getWallSize() const
{
    return m_wallSize;
}

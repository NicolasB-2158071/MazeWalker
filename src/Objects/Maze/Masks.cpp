#include "Masks.h"
#include "Lights.h"

Masks::Masks() : m_shader{ "src/Shaders/MaskVSShader.vs", "src/Shaders/MaskFSShader.fs" }
{
    m_shader.use();
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
    m_shader.bindUniformBlock("PointLightBlock", Lights::POINTLIGHT_BLOCK);
    initLighting();
}

void Masks::setLocations(const std::vector<glm::vec2>& locations)
{
    m_locations = locations;
    initObject();
}

void Masks::draw(Renderer& renderer)
{
    renderer.drawMasks(m_maskModel, m_shader, NUMBER_OF_MASKS);
}

void Masks::initMatrices()
{
    for (auto& location : m_locations)
    {
        glm::mat4 model{ 1.0f };
        model = glm::translate(model, glm::vec3{ location.x, 0.0f, location.y });
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
        model = glm::scale(model, glm::vec3{ 0.003f, 0.003f, 0.003f });
        m_locationsMatrices.push_back(std::move(model));
    }
}

void Masks::initObject()
{
    initMatrices();
    m_ivbo.setData(m_locationsMatrices.data(), sizeof(glm::mat4) * NUMBER_OF_MASKS);
    m_ivboNormalModel.setData(calculateNormalModels(m_locationsMatrices).data(), sizeof(glm::mat3) * NUMBER_OF_MASKS);
    m_maskModel = Model{ "res/Models/samurai-mask-sketch/Samurai_Mask_Sketch.obj", false, &m_ivbo, &m_ivboNormalModel };
}

void Masks::initLighting()
{
    m_shader.setVec3("material.specular", glm::vec3{ 0.8f, 0.8f, 0.8f });
    m_shader.setFloat("material.shininess", 64.0f);
}

std::vector<glm::mat3> Masks::calculateNormalModels(const std::vector<glm::mat4>& locations) const
{
    std::vector<glm::mat3> normalModels;
    for (const auto& location : locations)
    {
        glm::mat3 normalModel = glm::transpose(glm::inverse(location));
        normalModels.push_back(std::move(normalModel));
    }
    return normalModels;
}

// Eventmanger meegeven aan maze
// Shader aanpassen
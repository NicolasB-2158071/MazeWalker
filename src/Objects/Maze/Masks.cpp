#include "Masks.h"
#include "Lights.h"

#include "../../Camera/InteractionHandler.h"

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
    if (glfwGetTime() - m_startTimeSeeThrough > 3.0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    renderer.drawMasks(m_maskModel, m_shader, NUMBER_OF_MASKS);
}

void Masks::initMasksInput(EventManager* eventManager)
{
    eventManager->registerCallback(EventType::MOUSE_LEFT_CLICK, [this](EventInfo& info)
    {
        MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
        handleLeftClickPicking(); // Always from center for clicking
    });
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

void Masks::handleLeftClickPicking()
{
    InteractionHandler* ih{ InteractionHandler::getInstance() };
    glm::vec3 ray{ ih->calculateRayVectorFromCenter() };

    // Check for all masks if there is a collision
    int maskNumber{};
    for (auto& location : m_locations)
    {
        glm::vec3 center{ location.x + 0.01f, 0.0f, location.y + 0.01f };
        if (ih->isSphereRayCollisionFromCamera(ray, center, 0.5f, 8.0f))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            m_startTimeSeeThrough = glfwGetTime();
        }
        ++maskNumber;
    }
}
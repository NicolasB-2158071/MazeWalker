#include "BlackHole.h"

#include "../../Camera/InteractionHandler.h"

BlackHole::BlackHole() : m_shader{"src/Shaders/BlackHoleVSShader.vs", "src/Shaders/BlackHoleFSShader.fs"}, m_floorWidth{}, m_floorHeight{}
{
    m_shader.use();
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
}

void BlackHole::draw(Renderer& renderer)
{
    renderer.drawBlackHole(m_blackHoleModel, m_shader);
}

void BlackHole::initBlackHoleInput(EventManager* eventManager)
{
    eventManager->registerCallback(EventType::MOUSE_LEFT_CLICK, [this](EventInfo& info)
    {
        MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
        handleLeftClickPicking(); // Always from center for clicking
    });
}

void BlackHole::initObject(float floorWidth, float floorHeight)
{
    m_shader.use();
    m_floorWidth = floorWidth; // Nodig voor camera te zetten
    m_floorHeight = floorHeight;

    glm::mat4 model{ 1.0f };
    model = glm::translate(model, glm::vec3{ m_floorWidth - 0.5f, 1.0f, m_floorHeight - 0.5f });
    model = glm::scale(model, glm::vec3{ 0.2f, 0.2f, 0.2f});
    m_shader.setMat4("model", 1, GL_FALSE, model);
    m_blackHoleModel = Model{ "res/Models/sphere/sphere.obj", false };
    
    initAudio();
}

void BlackHole::initAudio()
{
    if (!m_backgroundMusic.openFromFile("res/Audio/Ambient.wav"))
    {
        std::cout << "ERROR loading black hole sound";
        return;
    }
    m_backgroundMusic.setPosition(m_floorWidth, 1.0f, m_floorHeight);
    m_backgroundMusic.setMinDistance(3.0f);
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.setVolume(50.0f);
    m_backgroundMusic.play();
}

void BlackHole::handleLeftClickPicking()
{
    InteractionHandler* ih{ InteractionHandler::getInstance() };
    glm::vec3 ray{ ih->calculateRayVectorFromCenter() };
    glm::vec3 center{ m_floorWidth - 0.5f, 1.0f, m_floorHeight - 0.5f };

    if (ih->isSphereRayCollisionFromCamera(ray, center, 0.2f, 8.0f))
    {
        glm::vec3 newPosition{ m_floorWidth / 2, 50.0f, m_floorHeight / 2 };
        m_backgroundMusic.setPosition(newPosition.x, newPosition.y, newPosition.z);
        ih->getCamera().setPositionLocked(newPosition);
    }
}

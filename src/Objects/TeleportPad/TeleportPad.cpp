#include "TeleportPad.h"

TeleportPad::TeleportPad(Camera& camera) : m_shader{"src/Shaders/TeleportPadVSShader.vs", "src/Shaders/TeleportPadFSShader.fs"}, m_isVisible{false}, m_camera{camera}
{
    m_shader.use();
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
    initObject();
    initAudio();
}

void TeleportPad::draw(Renderer& renderer)
{
    if (m_isVisible)
        renderer.drawTeleportPad(m_teleportPadModel, m_shader);
}

void TeleportPad::initObject()
{
    m_teleportPadModel = Model{ "res/Models/sm-teleporter/SM_Teleporter.fbx", false };
}

void TeleportPad::update(bool eKeyPressed)
{
    if (!eKeyPressed)
        return;

    if (m_camera.isTeleportSet())
    {
        glm::vec3 pos{ m_camera.getCameraPos() };
        m_shader.use();
        m_shader.setMat4("model", 1, GL_FALSE, setPosition(glm::vec3{ pos.x, 0.0f, pos.z }));
        m_isVisible = true;

        m_teleportSound.setBuffer(m_placingSound);
        m_teleportSound.play();
    }
    else
    {
        m_isVisible = false;

        m_teleportSound.setBuffer(m_teleportingSound);
        m_teleportSound.play();
    }
}

void TeleportPad::initAudio()
{
    if (!m_teleportingSound.loadFromFile("res/Audio/TeleportingSound.wav"))
    {
        std::cout << "ERROR loading teleport placing sound";
        return;
    }
    if (!m_placingSound.loadFromFile("res/Audio/PlacingSound.wav"))
    {
        std::cout << "ERROR loading teleporting sound";
        return;
    }

    m_teleportSound.setRelativeToListener(true);
    m_teleportSound.setVolume(25.0f);
}

glm::mat4 TeleportPad::setPosition(const glm::vec3& position)
{
    glm::mat4 model{ 1.0f };
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
    model = glm::scale(model, glm::vec3{0.01f, 0.01f, 0.01f});
    return model;
}

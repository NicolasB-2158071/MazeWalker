#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(float windowWidth, float windowHeight, EventManager* eventManager) : m_cameraPos{ 0.0f, 0.3f, 0.0f }, m_cameraFront{ 0.0f, 0.0f, -1.0f }, m_cameraUp{ 0.0f, 1.0f, 0.0f },
m_firstMouse{ true }, m_lastX{ windowWidth / 2 }, m_lastY{ windowHeight / 2 }, m_yaw{ -90.0f }, m_pitch{ 0.0f }, m_cameraSpeed{2.5f}, m_mouseSpeed{0.1f}
{
    initCameraInputs(eventManager);
}

void Camera::processKeyboardMovement(int keyPressed, float deltaTime)
{
    float cameraSpeed{ m_cameraSpeed * deltaTime };
    switch (keyPressed)
    {
    case GLFW_KEY_W:
        m_cameraPos += cameraSpeed * m_cameraFront;
        break;
    case GLFW_KEY_S:
        m_cameraPos -= cameraSpeed * m_cameraFront;
        break;
    case GLFW_KEY_A:
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed; // x waarde (één x coordinaat)
        break;
    case GLFW_KEY_D:
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed; // x waarde (één x coordinaat)
        break;
    }
    //m_cameraPos.y = 0.2f;
}

void Camera::processMouseMovement(double xpos, double ypos)
{
    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    m_yaw += (xpos - m_lastX) * m_mouseSpeed;
    m_pitch += (m_lastY - ypos) * m_mouseSpeed;

    m_lastX = xpos;
    m_lastY = ypos;

    if (m_pitch > 89.0f) // 90.0f is a lookAtFlip
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(direction);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Camera::setCameraSpeed(float cameraSpeed)
{
    m_cameraSpeed = cameraSpeed;
}

void Camera::setMouseSpeed(float mouseSpeed)
{
    m_mouseSpeed = mouseSpeed;
}

void Camera::newFocus()
{
    m_firstMouse = true;
}

void Camera::initCameraInputs(EventManager* eventManager)
{
    eventManager->registerCallback(EventType::MOUSE_MOVE, [this](EventInfo& info)
    {
        MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
        processMouseMovement(mouseInfo.xpos, mouseInfo.ypos);
    });
    // focus input
}

#include "Camera.h"
#include <GLFW/glfw3.h>
#include <cmath>

Camera::Camera(float windowWidth, float windowHeight, EventManager* eventManager) : m_lastX{ windowWidth / 2 }, m_lastY{ windowHeight / 2 },
    m_windowWidth{windowWidth}, m_windowHeight{windowHeight}
{
    m_projectionMatrix = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);
    initCameraInputs(eventManager);
}

void Camera::processKeyboardMovement(Window::keyboardPresses presses, float deltaTime)
{
    float cameraSpeed{ m_cameraSpeed * deltaTime };
    m_oldPos.x = m_cameraPos.x, m_oldPos.y = m_cameraPos.z;
    if (presses.key_w_active)
        m_cameraPos += cameraSpeed * m_cameraFront;
    if (presses.key_s_active)
        m_cameraPos -= cameraSpeed * m_cameraFront;
    if (presses.key_a_active)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed; // x waarde (één x coordinaat)
    if (presses.key_d_active)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed; // x waarde (één x coordinaat)

    processJumping(presses.key_space_active);
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

glm::mat4 Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}

glm::vec3 Camera::getCameraPos() const
{
    return m_cameraPos;
}

glm::vec3 Camera::getCameraDirection() const
{
    return m_cameraFront;
}

glm::vec2 Camera::getXZPosition() const
{
    return glm::vec2{m_cameraPos.x, m_cameraPos.z};
}

void Camera::rewindCamera()
{
    m_cameraPos.x = m_oldPos.x;
    m_cameraPos.z = m_oldPos.y;
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

// Heavily inspired by: https://antongerdelan.net/opengl/raycasting.html
glm::vec3 Camera::calculateRayVector(double mouseXpos, double mouseYpos) const
{
    // NDC + homogeneous clip coordinates
    glm::vec4 newRayTemp
    {
        (2.0f * mouseXpos) / m_windowWidth - 1.0f,
         1.0f - (2.0f * mouseYpos) / m_windowHeight,
        -1.0f,
         1.0f
    };

    // Eye camera coordinates
    newRayTemp = glm::inverse(m_projectionMatrix) * newRayTemp;
    newRayTemp = glm::vec4(newRayTemp.x, newRayTemp.y, -1.0f, 0.0f);

    // World coordinates
    glm::vec3 newRay{ glm::inverse(getViewMatrix()) * newRayTemp };
    newRay = glm::normalize(newRay);

    return newRay;
}

void Camera::initCameraInputs(EventManager* eventManager)
{
    eventManager->registerCallback(EventType::MOUSE_MOVE, [this](EventInfo& info)
    {
        MouseMovementInfo& mouseInfo{ static_cast<MouseMovementInfo&>(info) };
        processMouseMovement(mouseInfo.xpos, mouseInfo.ypos);
    });
}

void Camera::processJumping(bool spacePressed)
{
    // On ground
    if (m_onGround)
    {
        m_cameraPos.y = 0.5f;
        // Start of jump
        if (spacePressed)
            m_onGround = false; // Next frame process
        return;
    }

    m_velocityY += m_gravity;
    m_cameraPos.y += m_velocityY;
    if (m_cameraPos.y >= m_maxHeight && m_gravity > 0.0f)
        m_gravity *= -1;
    else if (m_cameraPos.y <= 0.5f && m_gravity < 0.0f)
    {
        m_onGround = true;
        m_velocityY = 0.0f;
        m_gravity *= -1;
    }
}

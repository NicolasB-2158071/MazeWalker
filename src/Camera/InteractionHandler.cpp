#include "InteractionHandler.h"

InteractionHandler* InteractionHandler::self = nullptr;

InteractionHandler::InteractionHandler(float windowWidth, float windowHeight, Camera& camera) : m_windowWidth{windowWidth}, m_windowHeight{windowHeight}, m_camera{camera}
{
    self = this;
}

InteractionHandler* InteractionHandler::getInstance()
{
    return self;
}

glm::vec3 InteractionHandler::calculateRayVector(double mouseXpos, double mouseYpos) const
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
    newRayTemp = glm::inverse(m_camera.getProjectionMatrix()) * newRayTemp;
    newRayTemp = glm::vec4(newRayTemp.x, newRayTemp.y, -1.0f, 0.0f);

    // World coordinates
    glm::vec3 newRay{ glm::inverse(m_camera.getViewMatrix()) * newRayTemp };
    newRay = glm::normalize(newRay);

    return newRay;
}

glm::vec3 InteractionHandler::calculateRayVectorFromCenter() const
{
	return calculateRayVector(m_windowWidth / 2, m_windowHeight / 2);
}

bool InteractionHandler::isSphereRayCollision(const glm::vec3& ray, const glm::vec3& origin, const glm::vec3& center, float radius, float maxLength) const
{
    float b{ glm::dot(ray, origin - center) };
    float c{ glm::dot((origin - center), (origin - center)) - radius * radius };

    // Check collision
    float length{ glm::length(center - origin) }; // Max range
    if (length < maxLength && b * b - c >= 0)
        return true;
    return false;
}

bool InteractionHandler::isSphereRayCollisionFromCamera(const glm::vec3& ray, const glm::vec3& center, float radius, float maxLength) const
{
    return isSphereRayCollision(ray, m_camera.getCameraPos(), center, radius, maxLength);
}

void InteractionHandler::setWindowDimensions(float windowWidth, float windowHeight)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}

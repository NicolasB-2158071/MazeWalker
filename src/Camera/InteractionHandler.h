#pragma once

#include "Camera.h"

class InteractionHandler
{

public:

	InteractionHandler(float windowWidth, float windowHeight, Camera& camera);
	static InteractionHandler* getInstance();

	// Heavily inspired by: https://antongerdelan.net/opengl/raycasting.html
	glm::vec3 calculateRayVector(double mouseXpos, double mouseYpos) const;
	glm::vec3 calculateRayVectorFromCenter() const;

	// https://antongerdelan.net/opengl/images/raysphere.png simpel sphere collision (better would be AABB)
	bool isSphereRayCollision(const glm::vec3& ray, const glm::vec3& origin, const glm::vec3& center, float radius, float maxLength) const;
	bool isSphereRayCollisionFromCamera(const glm::vec3& ray, const glm::vec3& center, float radius, float maxLength) const;

	void setWindowDimensions(float windowWidth, float windowHeight);

private:
	
	Camera& m_camera;

	float m_windowWidth;
	float m_windowHeight;

	// Singleton
	static InteractionHandler* self;
};
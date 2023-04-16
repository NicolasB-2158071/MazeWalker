#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../src/EventManager/EventManager.h"
#include "../Window/Window.h"

class Camera
{
public:
	Camera(float windowWidth, float windowHeight, EventManager* eventManager);

	void processKeyboardMovement(Window::keyboardPresses presses, float deltaTime);
	void processMouseMovement(double xpos, double ypos);

	glm::mat4 getViewMatrix() const;

	glm::vec2 getXZPosition() const;
	void rewindCamera();

	void setCameraSpeed(float cameraSpeed);
	void setMouseSpeed(float mouseSpeed);

	void newFocus(); // firstMouse

	// In window setFocus (geen processing doet)

private:
	// LookAt parameters
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	// For collision
	glm::vec2 m_oldPos;

	// Mouse variables
	bool m_firstMouse;
	float m_lastX;
	float m_lastY;
	float m_yaw;
	float m_pitch;
	void initCameraInputs(EventManager* eventManager);

	// Sensitivy variables
	float m_cameraSpeed;
	float m_mouseSpeed;

	// Jumping vars
	float m_gravity = 0.001f;
	float m_velocityY = 0.0f;
	float m_maxHeight = 1.0f;
	bool m_onGround = true;
	void processJumping(bool spacePressed);
};
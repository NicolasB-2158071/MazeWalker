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
	glm::mat4 getProjectionMatrix() const;
	void setWindowDimensions(float windowWidth, float windowHeight);

	glm::vec3 getCameraPos() const;
	glm::vec3 getCameraDirection() const;
	glm::vec2 getXZPosition() const;
	void rewindCamera();

	void setCameraSpeed(float cameraSpeed);
	void setMouseSpeed(float mouseSpeed);
	void setPositionLocked(const glm::vec3& position);
	bool isTeleportSet() const;

	void newFocus(); // firstMouse

private:
	// LookAt parameters
	glm::vec3 m_cameraPos = glm::vec3{ 0.1f, 0.5f, 0.1f };
	glm::vec3 m_cameraFront = glm::vec3{ 0.0f, 0.0f, 1.0f };
	glm::vec3 m_cameraUp = glm::vec3{ 0.0f, 1.0f, 0.0f }; // Switched camera looking to behind!!
	bool m_locked = false;;

	// Window parameters
	glm::mat4 m_projectionMatrix;

	// For collision
	glm::vec2 m_oldPos;


	// Mouse variables
	bool m_firstMouse = true;
	float m_lastX;
	float m_lastY;
	float m_yaw = 90.0f;
	float m_pitch = 0.0f;
	void initCameraInputs(EventManager* eventManager);

	// Sensitivy variables
	float m_cameraSpeed = 2.5f;
	float m_mouseSpeed = 0.1f;

	// Jumping vars
	float m_gravity = 0.001f;
	float m_velocityY = 0.0f;
	float m_maxHeight = 1.0f;
	bool m_onGround = true;
	void processJumping(bool spacePressed);

	// Dashing vars
	double m_startDashTime = 0.0;
	bool m_canDash = true;
	bool m_isDashing = false;
	void processDash(float cameraSpeed, bool fKeyPressed);

	// Teleport
	glm::vec3 m_teleportPos = m_cameraPos;
	bool m_teleportSet = false;
	double m_debounceKeyPress = 0.0;
	void processTeleport(bool eKeyPressed);
};
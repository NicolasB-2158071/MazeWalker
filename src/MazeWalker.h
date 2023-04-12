#pragma once

#include <glad/glad.h>
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "EventManager/EventManager.h"

class MazeWalker
{
public:
	MazeWalker(int windowWidth, int windowHeight, const char* titel);
	//~MazeWalker();

	void run();

private:
	EventManager m_eventManager;
	Window m_window;
	Camera m_camera;

	// Renderer
	// maze
	// floor
	// skybox

	// Input ook anders wegens springen (zwaartekracht!!)
	// Random maze genereren is een algoritme (verschillende)

	bool m_running;
	float m_deltaTime;
	float m_lastFrameTime;
	void updateDeltaTime();

	bool m_focus;

	void processKeyBoardMovement(); // Keyboardmovement best processed per frame (or using some constant deltaTime to synch keyCallback events)
	void initApplicationInputs();
};
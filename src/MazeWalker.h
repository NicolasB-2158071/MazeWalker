#pragma once

#include "Window/Window.h"
#include "Camera/Camera.h"
#include "EventManager/EventManager.h"
#include "Renderer/Renderer.h"

#include "Objects/Maze/Maze.h"
#include "Objects/Skybox/Skybox.h"

class MazeWalker
{
public:
	MazeWalker(float windowWidth, float windowHeight, const char* titel);
	//~MazeWalker();

	void run();

private:
	EventManager m_eventManager;
	Window m_window;
	Camera m_camera;
	Renderer m_renderer;

	std::unique_ptr<Maze> m_maze;
	std::unique_ptr<Skybox> m_skybox;

	// Input ook anders wegens springen (zwaartekracht!!)
	// Random maze genereren is een algoritme (verschillende)

	bool m_running;
	float m_deltaTime = 0.0f;
	float m_lastFrameTime = 0.0f;
	void updateDeltaTime();

	bool m_focus = false;

	void processKeyBoardMovement(); // Keyboardmovement best processed per frame (or using some constant deltaTime to synch keyCallback events)
	void initApplicationInputs();
};
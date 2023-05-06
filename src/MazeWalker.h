#pragma once

#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Camera/InteractionHandler.h"
#include "EventManager/EventManager.h"
#include "Renderer/Renderer.h"

#include "Objects/Maze/Maze.h"
#include "Objects/TeleportPad/TeleportPad.h"
#include "Objects/Meteorite/Meteorite.h"
#include "Objects/Skybox/Skybox.h"

class MazeWalker
{
public:
	MazeWalker(float windowWidth, float windowHeight, const char* titel);

	void run();

private:
	EventManager m_eventManager;
	Window m_window;
	Camera m_camera;
	InteractionHandler m_interactionHandler;
	Renderer m_renderer;

	std::unique_ptr<Maze> m_maze;
	std::unique_ptr<TeleportPad> m_teleportPad; // Property that actually belongs tho a Player class or something
	std::unique_ptr<Meteorite> m_meteorites;
	std::unique_ptr<Skybox> m_skybox;

	bool m_running;
	float m_deltaTime = 0.0f;
	float m_lastFrameTime = 0.0f;
	void updateDeltaTime();

	bool m_focus = false;

	void processKeyBoardMovement(); // Keyboardmovement best processed per frame instead of EventManager (or using some constant deltaTime to synch keyCallback events)
	void initApplicationInputs();
};
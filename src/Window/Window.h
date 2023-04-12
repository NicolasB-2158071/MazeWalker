#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../src/EventManager/EventManager.h"

// Opens a window, context and registers callbacks
class Window
{
public:
	Window(float width, float height, const std::string& titel, EventManager* eventManager);
	~Window();

	void update();
	
	int getCurrentKeyPress() const;
	void setCursorFocus(bool enabled);

	float getWidth() const;
	float getHeight() const;

	bool SUCCESS;

private:
	GLFWwindow* m_window;

	void initWindowCallbacks();

	float m_width;
	float m_height;
	std::string m_titel;

	bool init();
	void destruct() const;
};
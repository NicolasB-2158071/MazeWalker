#pragma once

#include <GLFW/glfw3.h>
#include <string>

#include "../src/EventManager/EventManager.h"

// Opens a window, context and registers callbacks
class Window
{
public:
	Window(int width, int height, const std::string& titel, EventManager* eventManager);
	~Window();

	void update();
	
	int getCurrentKeyPress() const;
	void setCursorFocus(bool enabled);

private:
	GLFWwindow* m_window;

	void initWindowCallbacks();

	int m_width;
	int m_height;
	std::string m_titel;

	bool init();
	void destruct() const;
};
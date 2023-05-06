#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../src/EventManager/EventManager.h"

// Opens a window, context and registers callbacks
class Window
{
public:

	struct keyboardPresses
	{
		bool key_w_active{ false };
		bool key_s_active{ false };
		bool key_a_active{ false };
		bool key_d_active{ false };
		bool key_f_active{ false };
		bool key_esc_active{ false };
		bool key_space_active{ false };
	};

	Window(float width, float height, const std::string& titel, EventManager* eventManager);
	~Window();

	void update();
	
	keyboardPresses processKeyboardPresses();
	void setCursorFocus(bool enabled);

	float getWidth() const;
	float getHeight() const;


	bool SUCCESS;

private:
	GLFWwindow* m_window;
	keyboardPresses m_presses;

	void initWindowCallbacks();

	float m_width;
	float m_height;
	std::string m_titel;

	bool init();
	void destruct() const;
};
#include "Window.h"

#include <iostream>

Window::Window(float width, float height, const std::string& titel, EventManager* eventManager) : m_width{ width }, m_height{ height }, m_titel{ titel }
{
    if (!init())
    {
        SUCCESS = false;
        destruct();
        return;
    }
    SUCCESS = true;
    glfwSetWindowUserPointer(m_window, eventManager);
    initWindowCallbacks();
}

Window::~Window()
{
    destruct();
}

bool Window::init()
{
    // Initialize glfw window en set OpenGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(m_width, m_height, m_titel.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "ERROR: failed to create a window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Window::initWindowCallbacks()
{
   glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
    {
           EventManager* manager{ static_cast<EventManager*>(glfwGetWindowUserPointer(window)) };
           manager->callbackEvent(EventType::WINDOW_CLOSE, EventInfo{});
    });
   glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        EventManager* manager{ static_cast<EventManager*>(glfwGetWindowUserPointer(window)) };
        manager->callbackEvent(EventType::WINDOW_RESIZE, WindowResizeInfo{ width, height });
    });
   glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
    {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
            return;
        EventManager* manager{ static_cast<EventManager*>(glfwGetWindowUserPointer(window)) };
        manager->callbackEvent(EventType::MOUSE_MOVE, MouseMovementInfo{ xpos, ypos });
    });
   glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            EventManager* manager{ static_cast<EventManager*>(glfwGetWindowUserPointer(window)) };
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
                manager->callbackEvent(EventType::WINDOW_FOCUS, EventInfo{});
            else
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                manager->callbackEvent(EventType::MOUSE_CLICK, MouseMovementInfo{xpos, ypos});
            }
        }
    });
}

void Window::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

Window::keyboardPresses Window::processKeyboardPresses()
{
    m_presses.key_w_active = (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS);
    m_presses.key_s_active = (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS);
    m_presses.key_a_active = (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS);
    m_presses.key_d_active = (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS);
    m_presses.key_esc_active = (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    m_presses.key_space_active = (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS);

    return m_presses;
}

bool Window::isAKeyPressed() const
{
    return m_presses.key_w_active || m_presses.key_s_active || m_presses.key_a_active || m_presses.key_d_active || m_presses.key_space_active;
}

void Window::setCursorFocus(bool enabled)
{
    if (enabled)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

float Window::getWidth() const
{
    return m_width;
}

float Window::getHeight() const
{
    return m_height;
}

void Window::destruct() const
{
    glfwTerminate();
}
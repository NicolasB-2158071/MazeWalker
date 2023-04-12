#include "MazeWalker.h"

#include <iostream>

// TEMP
#include "Objects/Maze/Floor.h"
#include <string>

MazeWalker::MazeWalker(float windowWidth, float windowHeight, const char* titel) : m_window{ windowWidth, windowHeight, titel, &m_eventManager}, m_camera{ windowWidth , windowHeight, &m_eventManager},
m_renderer{ "src/Shaders/CubVShader.vs", "src/Shaders/CubFShader.fs" }, m_running{ m_window.SUCCESS}, m_deltaTime{}, m_lastFrameTime{}, m_focus{false}
{
    // Maze uit file gelezen worden
    m_renderer.setProjectionMatrix(glm::perspective(glm::radians(45.0f), m_window.getWidth() / m_window.getHeight(), 0.1f, 100.0f));
    initApplicationInputs();
}

void MazeWalker::run()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //double prevTime{};
    //double crntTime{};
    //double timeDiff;
    //unsigned int counter{};

    Floor floor{ glm::vec2{1.0f, 1.0f} };

    while (m_running)
    {
       /* crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0)
            glfwSetWindowTitle(m_window.m_window, std::to_string((1.0 / timeDiff) * counter).c_str());*/

        updateDeltaTime();
        processKeyBoardMovement();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderer.setViewMatrix(m_camera.getViewMatrix());
        floor.draw(m_renderer);

        // Rendering gebeuren
        // Draw skybox
        // Draw maze -> floor, walls

        m_window.update();
    }
}

void MazeWalker::updateDeltaTime()
{
    float currentFrameTime = static_cast<float>(glfwGetTime()); // In het begin want tijd wordt beïnvloedt door drawing
    m_deltaTime = currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = currentFrameTime;
}

// Keyboard input per frame voor synchronizatie (de rest adhv callbacks)
void MazeWalker::processKeyBoardMovement()
{
    int currentKeyPress{ m_window.getCurrentKeyPress() };
    if (currentKeyPress == -1)
        return;

    if (currentKeyPress == GLFW_KEY_ESCAPE)
    {
        m_focus = false;
        m_window.setCursorFocus(false);
        return;
    }
    if (m_focus)
        m_camera.processKeyboardMovement(currentKeyPress, m_deltaTime);
}

void MazeWalker::initApplicationInputs()
{
    m_eventManager.registerCallback(EventType::WINDOW_CLOSE, [this](EventInfo& info) {m_running = false; });
    m_eventManager.registerCallback(EventType::WINDOW_RESIZE, [this](EventInfo& info)
    {
        glViewport(0, 0, static_cast<WindowResizeInfo&>(info).width, static_cast<WindowResizeInfo&>(info).height);
    });
    // WORDT STEEDS BIJ EEN CLICK OPGEROEPEN!!!
    m_eventManager.registerCallback(EventType::WINDOW_FOCUS, [this](EventInfo& info)
    {
        m_focus = true;
        m_camera.newFocus();
        m_window.setCursorFocus(true);
    });
}
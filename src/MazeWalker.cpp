#include "MazeWalker.h"

#include <iostream>

MazeWalker::MazeWalker(float windowWidth, float windowHeight, const char* titel) : m_window{ windowWidth, windowHeight, titel, &m_eventManager}, m_camera{ windowWidth , windowHeight, &m_eventManager},
m_renderer{ m_camera }, m_running { m_window.SUCCESS }
{
    m_maze = std::make_unique<Maze>();
    m_skybox = std::make_unique<Skybox>(); m_skybox->initObject();

    m_maze->getLights().setCamera(&m_camera);
    m_maze->getLights().initLightsInput(&m_eventManager);

    initApplicationInputs();
}

void MazeWalker::run()
{
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);

    while (m_running)
    {
        updateDeltaTime();
        processKeyBoardMovement();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderer.prepare(); // View matrix

        m_maze->draw(m_renderer);
        // Models
        m_skybox->draw(m_renderer); // Draw always as last

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
    Window::keyboardPresses presses{ m_window.processKeyboardPresses() };
    if (presses.key_esc_active)
    {
        m_focus = false;
        m_window.setCursorFocus(false);
        return;
    }
    if (m_focus)
    {
        m_camera.processKeyboardMovement(presses, m_deltaTime);
        if (m_window.isAKeyPressed() && m_maze->isWallColision(m_camera.getXZPosition()))
            m_camera.rewindCamera();
    }
}

void MazeWalker::initApplicationInputs()
{
    m_eventManager.registerCallback(EventType::WINDOW_CLOSE, [this](EventInfo& info) {m_running = false; });
    m_eventManager.registerCallback(EventType::WINDOW_RESIZE, [this](EventInfo& info)
    {
        glViewport(0, 0, static_cast<WindowResizeInfo&>(info).width, static_cast<WindowResizeInfo&>(info).height);
    });
    
    m_eventManager.registerCallback(EventType::WINDOW_FOCUS, [this](EventInfo& info)
    {
        //if (m_focus)
        //{
        //    glPolygonMode(GL_FRONT_AND_BACK, m_wireframe ? GL_FILL : GL_LINE);
        //    m_wireframe = !m_wireframe;
        //}
        m_focus = true;
        m_camera.newFocus();
        m_window.setCursorFocus(true);
    });
}
#include "MazeWalker.h"

#include <SFML/Audio.hpp>
#include <SFML/Audio/Listener.hpp>

#include <iostream>

MazeWalker::MazeWalker(float windowWidth, float windowHeight, const char* titel) : m_window{ windowWidth, windowHeight, titel, &m_eventManager}, m_camera{ windowWidth , windowHeight, &m_eventManager},
m_interactionHandler{ windowWidth, windowHeight, m_camera}, m_renderer{m_camera}, m_running{m_window.SUCCESS}
{
    m_maze = std::make_unique<Maze>(&m_eventManager);
    m_skybox = std::make_unique<Skybox>(); m_skybox->initObject();

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

        glm::vec3 cP{ m_camera.getCameraPos() };
        glm::vec3 cD{ m_camera.getCameraDirection() };

        sf::Listener::setPosition(cP.x, cP.y, cP.z);
        sf::Listener::setDirection(cD.x, cD.y, cD.z);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_renderer.prepare(); // View matrix

        m_maze->draw(m_renderer);
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
       /* if (m_maze->isCollision(m_camera.getXZPosition()))
            m_camera.rewindCamera();*/
    }
}

void MazeWalker::initApplicationInputs()
{
    m_eventManager.registerCallback(EventType::WINDOW_CLOSE, [this](EventInfo& info) {m_running = false; });
    m_eventManager.registerCallback(EventType::WINDOW_RESIZE, [this](EventInfo& info)
    {
        WindowResizeInfo& resizeInfo{ static_cast<WindowResizeInfo&>(info) };
        m_camera.setWindowDimensions(resizeInfo.width, resizeInfo.height); // Update projectionMatrix
        m_interactionHandler.setWindowDimensions(resizeInfo.width, resizeInfo.height); // For picking in the middle
        m_renderer.updateProjectionMatrix(); // Rendering
        glViewport(0, 0, resizeInfo.width, resizeInfo.height);
    });
    
    m_eventManager.registerCallback(EventType::WINDOW_FOCUS, [this](EventInfo& info)
    {
        m_focus = true;
        m_camera.newFocus();
        m_window.setCursorFocus(true);
    });
}
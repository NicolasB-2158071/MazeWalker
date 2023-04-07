#include "MazeWalker.h"

#include <iostream>

// TEMP
#include "Shaders/Shader.h"
#include "VertexBuffer/VertexBuffer.h"
#include "VertexBuffer/VertexBufferLayout.h"
#include "VertexArray/VertexArray.h"
#include "Textures/Texture.h"

MazeWalker::MazeWalker(int windowWidth, int windowHeight, const char* titel) : m_window{ windowWidth, windowHeight, titel, &m_eventManager},
m_camera{ windowWidth , windowHeight, &m_eventManager}, m_running{ true }, m_deltaTime{}, m_lastFrameTime{}, m_focus{false}
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        m_running = false;
    }
    initApplicationInputs();
}

void MazeWalker::run()
{
    float vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Shader shader{
        "src/Shaders/MyVShader.vs",
        "src/Shaders/MyFShader.fs"
    };

    VertexBuffer VBO{ vertices, sizeof(vertices) };
    VertexArray VAO{};

    VertexBufferLayout VBL{};
    VBL.addAttribute(3, GL_FLOAT, GL_FALSE);
    VBL.addAttribute(2, GL_FLOAT, GL_FALSE);

    VAO.connectVertexBuffer(VBO, VBL);

    Texture textureOne{ "res/container.jpg", GL_RGB };
    Texture textureTwo{ "res/awesomeface.png", GL_RGBA };

    shader.use();
    shader.setInt("ourTexture1", 0); // Set slot
    shader.setInt("ourTexture2", 1);

    glm::mat4 model = glm::mat4(1.0f);
    shader.setTransformation("model", 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 projection; // Left hand + clipping
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.setTransformation("projection", 1, GL_FALSE, glm::value_ptr(projection));

    // ---------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);
    while (m_running)
    {
        updateDeltaTime();
        processKeyBoardMovement();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set state
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Use state

        textureOne.activeAndBind(GL_TEXTURE0);
        textureTwo.activeAndBind(GL_TEXTURE1);

        glm::mat4 view = m_camera.getViewMatrix();
        shader.setTransformation("view", 1, GL_FALSE, glm::value_ptr(view));

        VAO.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

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
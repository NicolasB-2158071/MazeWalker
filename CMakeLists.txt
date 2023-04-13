cmake_minimum_required(VERSION 3.24)
project(opengl_project)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

set(LIBS glfw3 opengl32)

add_library(GLAD "glad.c")
set(LIBS ${LIBS} GLAD)

include_directories(${CMAKE_SOURCE_DIR}/includes)
add_executable(opengl_project "src/main.cpp" "src/Shaders/Shader.h" "src/Shaders/Shader.cpp" stb_image.h "stb_image.cpp" "src/Buffers/VertexBuffer.h" "src/Buffers/VertexBuffer.cpp" "src/Camera/Camera.h" "src/Camera/Camera.cpp" "src/Window/Window.h" "src/Window/Window.cpp" "src/EventManager/EventManager.h" "src/EventManager/EventInfo.h" "src/EventManager/EventManager.cpp" "src/MazeWalker.h" "src/MazeWalker.cpp" "src/Buffers/VertexArray.h" "src/Buffers/VertexArray.cpp" "src/Buffers/VertexBufferLayout.h" "src/Buffers/VertexBufferLayout.cpp" "src/Textures/Texture.h" "src/Textures/Texture.cpp" "src/Renderer/Renderer.h" "src/Renderer/Renderer.cpp" "src/Objects/Maze/Maze.h" "src/Objects/Maze/Floor.h" "src/Objects/Maze/Walls.h" "src/Objects/Skybox.h" "src/Buffers/IndexBuffer.h" "src/Buffers/IndexBuffer.cpp" "src/Objects/Maze/Floor.cpp" "src/Objects/Maze/Walls.cpp" "src/Objects/Maze/Maze.cpp" "src/Objects/Maze/MazeReader.h" "src/Objects/Maze/MazeReader.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "mazeWalker")
target_link_libraries(opengl_project ${LIBS})

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Buffers/VertexArray.h"
#include "../Textures/Texture.h"
#include "../Shaders/Shader.h"


//struct quad
//{
//	/*glm::vec3 pos;
//	glm::vec3 normal;
//	glm::vec2 tex;*/
//
//	// Mesh object???
//};

class Renderer
{
public:
	Renderer(const char* vertexShaderPath, const char* fragmentShaderPath);

	void setProjectionMatrix(const glm::mat4& projection);
	void setViewMatrix(const glm::mat4& viewMatrix); // Valt te zien

	void drawFloor(const VertexArray& vao, const glm::vec2& size, const Texture& texture);
	//void drawWalls(const glm::vec3& position, const glm::vec3& size, const Texture& texture);

private:
	Shader m_shader;
};

// Starten met één renderer (quad)
// Drawing van object compositie renderer
// render skybox
// render maze (ook lichtbronnen objecten)
// render floor
// -> textures, positie, grootte
// Shader staat vast (voor lighting moet posities gekend zijn, moet geset worden)
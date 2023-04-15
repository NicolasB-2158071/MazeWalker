#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Camera/Camera.h"
#include "../Buffers/VertexArray.h"
#include "../Textures/Texture.h"
#include "../Shaders/Shader.h"


class Renderer
{
public:
	Renderer(Camera& camera);

	void drawFloor(const VertexArray& vao, const Shader& shader, const Texture& texture);
	void drawWalls(const VertexArray& vao, const Shader& shader, const Texture& texture, int amount);

private:
	Camera& m_camera;
};

// Starten met één renderer (quad)
// Drawing van object compositie renderer
// render skybox
// render maze (ook lichtbronnen objecten)
// render floor
// -> textures, positie, grootte
// Shader staat vast (voor lighting moet posities gekend zijn, moet geset worden)
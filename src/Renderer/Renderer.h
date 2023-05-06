#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Camera/Camera.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/UniformBuffer.h"
#include "../Textures/Texture.h"
#include "../Textures/Cubemap.h"
#include "../Shaders/Shader.h"
#include "../Objects/Model.h"

class Renderer
{
public:
	const static unsigned int TRANSFORMATION_BLOCK = 0;

	Renderer(Camera& camera);
	void prepare();
	void updateProjectionMatrix();

	void drawFloor(const VertexArray& vao, const Shader& shader, const Texture& texture);
	void drawWalls(const VertexArray& vao, const Shader& shader, const Texture& texture, int amount);
	void drawSkybox(const VertexArray& vao, const Shader& shader, const Cubemap& cubemap);

	void drawLights(Model& lightModel, const Shader& shader, int amount);
	void drawMasks(Model& maskModel, const Shader& shader, int amount);

private:
	Camera& m_camera;
	UniformBuffer m_cameraBuffer;
};

// Uniform buffer object
// Prepare functie
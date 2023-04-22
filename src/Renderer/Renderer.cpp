#include "Renderer.h"

Renderer::Renderer(Camera& camera) : m_camera{camera}, m_cameraBuffer{2 * sizeof(glm::mat4), TRANSFORMATION_BLOCK }
{
	m_cameraBuffer.bind();
	m_cameraBuffer.addData(0, sizeof(glm::mat4), glm::value_ptr(m_camera.getProjectionMatrix()));
}

void Renderer::prepare()
{
	m_cameraBuffer.bind();
	m_cameraBuffer.addData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_camera.getViewMatrix()));
}

void Renderer::drawFloor(const VertexArray& vao, const Shader& shader, const Texture& texture)
{
	glEnable(GL_BLEND);
	shader.use();

	texture.activeAndBind(0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisable(GL_BLEND);
}

// Eerst scaling dan translatie (omgekeerde volgorde in code!!)
void Renderer::drawWalls(const VertexArray& vao, const Shader& shader, const Texture& texture, int amount)
{
	shader.use();

	texture.activeAndBind(0);
	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}

void Renderer::drawSkybox(const VertexArray& vao, const Shader& shader, const Cubemap& cubemap)
{
	glDepthFunc(GL_LEQUAL);
	shader.use();

	cubemap.activeAndBind(0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}

void Renderer::drawLights(const VertexArray& vao, const Shader& shader, int amount)
{
	shader.use();

	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}

#include "Renderer.h"

Renderer::Renderer(Camera& camera) : m_camera{camera} {}

void Renderer::drawFloor(const VertexArray& vao, const Shader& shader, const Texture& texture)
{
	shader.use();
	shader.setMat4("view", 1, GL_FALSE, m_camera.getViewMatrix());

	texture.activeAndBind(0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Eerst scaling dan translatie (omgekeerde volgorde in code!!)
void Renderer::drawWalls(const VertexArray& vao, const Shader& shader, const Texture& texture, int amount)
{
	shader.use();
	shader.setMat4("view", 1, GL_FALSE, m_camera.getViewMatrix());

	texture.activeAndBind(0);
	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}

void Renderer::drawSkybox(const VertexArray& vao, const Shader& shader, const Cubemap& cubemap)
{
	glDepthFunc(GL_LEQUAL);
	shader.use();
	shader.setMat4("view", 1, GL_FALSE, glm::mat4(glm::mat3(m_camera.getViewMatrix()))); // Translation gone

	cubemap.activeAndBind(0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}
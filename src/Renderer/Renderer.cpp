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
	//m_shader.use();
	//glm::mat4 model{ 1.0f };
	//model = glm::translate(model, glm::vec3{ 0.0f, size.y, 0.0f }); // vanaf origin point
	//m_shader.setMat4("model", 1, GL_FALSE, glm::scale(model, size));

	shader.use();
	shader.setMat4("view", 1, GL_FALSE, m_camera.getViewMatrix());

	texture.activeAndBind(0);
	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}

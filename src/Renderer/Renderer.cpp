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

void Renderer::updateProjectionMatrix()
{
	m_cameraBuffer.bind();
	m_cameraBuffer.addData(0, sizeof(glm::mat4), glm::value_ptr(m_camera.getProjectionMatrix()));
}

void Renderer::drawFloor(const VertexArray& vao, const Shader& shader, const Texture& texture)
{
	shader.use();

	texture.activeAndBind(GL_TEXTURE0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Eerst scaling dan translatie (omgekeerde volgorde in code!!)
void Renderer::drawWalls(const VertexArray& vao, const Shader& shader, const Texture& texture, int amount)
{
	shader.use();

	texture.activeAndBind(GL_TEXTURE0);
	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}

void Renderer::drawSkybox(const VertexArray& vao, const Shader& shader, const Cubemap& cubemap)
{
	glDepthFunc(GL_LEQUAL);
	shader.use();

	cubemap.activeAndBind(GL_TEXTURE0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}

void Renderer::drawMeteorites(Model& meteoriteModel, const Shader& shader, int amount)
{
	shader.use();
	meteoriteModel.draw(shader, amount);
}

void Renderer::drawLights(Model& lightModel, const Shader& shader, int amount)
{
	shader.use();
	lightModel.draw(shader, amount);
}

void Renderer::drawMasks(Model& maskModel, const Shader& shader, int amount)
{
	shader.use();
	maskModel.draw(shader, amount);
}

void Renderer::drawBlackHole(Model& blackHoleModel, const Shader& shader)
{
	shader.use();
	shader.setFloat("time", glfwGetTime());

	blackHoleModel.draw(shader, 1);
}

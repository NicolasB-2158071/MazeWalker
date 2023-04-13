#include "Renderer.h"

//Renderer::Renderer()
//{
//    /*m_shader.use();
//    m_shader.setMat4("projection", 1, false, projection);*/
//}

Renderer::Renderer(const char* vertexShaderPath, const char* fragmentShaderPath) : m_shader{ vertexShaderPath, fragmentShaderPath }
{
	m_shader.use();
	m_shader.setInt("textureOne", 0);
}

void Renderer::setProjectionMatrix(const glm::mat4& projection)
{
	m_shader.use();
	m_shader.setMat4("projection", 1, false, projection);
}

void Renderer::setViewMatrix(const glm::mat4& viewMatrix)
{
	m_shader.use();
	m_shader.setMat4("view", 1, false, viewMatrix);
}

void Renderer::drawFloor(const VertexArray& vao, const glm::vec2& size, const Texture& texture)
{
	m_shader.use();
	m_shader.setMat4("model", 1, GL_FALSE, glm::scale(glm::mat4{ 1.0f }, glm::vec3{ size.x, 0.0f, size.y}));

	texture.activeAndBind(0);
	vao.bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::drawWalls(const VertexArray& vao, const glm::vec3& size, const Texture& texture, int amount)
{
	m_shader.use();
	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3{ 0.0f, size.y, 0.0f }); // Floor level, later ook x en z naar start player
	m_shader.setMat4("model", 1, GL_FALSE, glm::scale(model, glm::vec3{ size.x, size.y, size.z }));

	texture.activeAndBind(0);
	vao.bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, amount);
}
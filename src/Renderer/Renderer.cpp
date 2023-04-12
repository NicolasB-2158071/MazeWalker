#include "Renderer.h"

//Renderer::Renderer()
//{
//    /*m_shader.use();
//    m_shader.setMat4("projection", 1, false, projection);*/
//}

void Renderer::setViewMatrix(const glm::mat4& viewMatrix)
{
	m_shader.use();
	m_shader.setMat4("view", 1, false, viewMatrix);
}

void Renderer::drawFloor(const glm::vec3& position, const glm::vec3& size, const Texture& texture)
{
	// Ook VAO meegeven aan renderer!!!
	// Renderer bevat shader, view, projection matrix
	
//	glm::mat4 model{ 1.0f };
//	model = glm::scale(model, size);
//	model = glm::translate(model, position);
//    m_shader.use();
//    m_shader.setMat4("model", 1, false, model);
//    
//    texture.activeAndBind(0);
////    m_vao.bind();
//    glDrawArrays(GL_TRIANGLES, 0, 36);
}
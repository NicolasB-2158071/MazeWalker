#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<aTexture>& textures) :
	m_vbo{ &vertices[0], sizeof(Vertex) * vertices.size() }, m_ibo{ &indices[0], sizeof(unsigned int) * indices.size() }, m_textures{ textures }
{
	setupMesh();
}

void Mesh::draw(const Shader& shader)
{
	shader.use();

	m_vao.bind();
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}

void Mesh::setupMesh()
{
	VertexBufferLayout vbl{};
	vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
	vbl.addAttribute(2, GL_FLOAT, GL_FALSE);
	vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

	m_vao.connectVertexBuffer(m_vbo, vbl);
	m_ibo.bind();
	m_vao.unbind();
}

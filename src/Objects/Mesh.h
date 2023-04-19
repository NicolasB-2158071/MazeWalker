#pragma once

#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Textures/Texture.h"
#include "../Shaders/Shader.h"

class Mesh
{
public:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 tex;
		glm::vec3 normal;
	};

	struct aTexture
	{
		Texture texture;
		std::string name;
	};

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<aTexture>& textures);
	
	void draw(const Shader& shader);


private:
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;
	VertexArray m_vao;

	std::vector<aTexture> m_textures;

	void setupMesh();
};
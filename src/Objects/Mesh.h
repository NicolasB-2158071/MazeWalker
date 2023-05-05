#pragma once

#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Textures/Texture.h"
#include "../Shaders/Shader.h"

#define MAX_BONE_INFLUENCE 4

class Mesh
{
public:
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 tex;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		int boneIDs[MAX_BONE_INFLUENCE];
		float weights[MAX_BONE_INFLUENCE];
	};

	struct aTexture
	{
		Texture texture;
		std::string name;
		std::string path;
	};

	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<aTexture>& textures,
		const VertexBuffer* ivbo, const VertexBuffer* ivboNormalModel);

	void draw(const Shader& shader, int instancingCount);

private:
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;
	VertexArray m_vao;

	size_t m_indicesSize;
	std::vector<aTexture> m_textures;

	void setupMesh(const VertexBuffer* ivbo, const VertexBuffer* ivboNormalModel);
};
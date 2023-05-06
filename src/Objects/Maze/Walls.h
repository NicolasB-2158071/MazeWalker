#pragma once

#include "../../Renderer/Renderer.h"

class Walls
{
public:
	Walls(const glm::vec3& wallSize);

	void draw(Renderer& renderer);
	void initObject(int amount, const std::vector<glm::vec2>& locations);


	bool isWallColision(const glm::vec2& cameraPos) const;
	glm::vec3 getWallSize() const;


private:
	VertexArray m_vao;
	Texture m_texture;
	Shader m_shader;

	glm::vec3 m_wallSize;
	std::vector<glm::vec2> m_wallsXZLocations; // Left top point of rectangle
	std::vector<glm::mat4> m_wallLocationMatrices;
	int m_amount = 1;
	void calculateXZLocations(const std::vector<glm::vec2>& offsets);
	void initMatrices(const std::vector<glm::vec2>& offsets);

	void initLighting();
	glm::mat4 calculateModel(int xOffset, int zOffset) const;
	std::vector<glm::mat3> calculateNormalModels(const std::vector<glm::mat4>& locations) const;

	const float OFFSET = 0.05f;
};
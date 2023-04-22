#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class MazeBuilder
{
public:
	MazeBuilder(const glm::vec3& wallSize);

	void readLocations(const char* mazePath);

	std::vector<glm::mat4>& getWallsLocationMatrices();
	const std::vector<glm::vec2>& getWallsXZLocations() const;
	glm::vec3 getWallSize() const;
	int getWallAmount() const;

	std::vector<glm::vec2> getRandomLightPositions(int quantity) const;

	float getWidth() const;
	float getHeight() const;

private:
	int m_width;
	int m_height;
	int m_wallAmount;
	glm::vec3 m_wallSize;
	std::vector<glm::mat4> m_wallLocatioMatrices;
	std::vector<glm::vec2> m_wallsXZLocations; // Left top point of rectangle

	glm::mat4 calculateModel(int xOffset, int zOffset) const;
	bool isWall(const glm::vec2& location) const;
};
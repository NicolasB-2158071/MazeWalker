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

	glm::mat4* getWallsLocationMatrices();
	const std::vector<glm::vec2>& getWallsXZLocations() const;
	glm::vec3 getWallSize() const;

	int getWallAmount() const;
	float getWidth() const;
	float getHeight() const;

	// Weten waar player start voor vloor ook te tekenen en translatie muren

private:
	int m_width;
	int m_height;
	int m_wallAmount;
	glm::vec3 m_wallSize;
	std::vector<glm::mat4> m_wallLocatioMatrices;
	std::vector<glm::vec2> m_wallsXZLocations; // Left top point of rectangle
	// x, z links bottom bijhouden

	glm::mat4 calculateModel(int xOffset, int zOffset) const;
};
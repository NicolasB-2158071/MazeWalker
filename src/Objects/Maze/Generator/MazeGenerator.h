#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <random>

class MazeGenerator
{
public:

	virtual void generateMaze(int width, int height) = 0;
	virtual std::vector<glm::vec2> getWallLocations() const = 0;
};
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "PrimGenerator.h"
#include "../Walls.h"

class MazeBuilder
{
public:
	MazeBuilder(const char* mazeFile = nullptr);

	void readLocations(const char* mazePath);
	const std::vector<glm::vec2>& getWallOffsets() const;

	int getWallAmount() const;

	std::vector<glm::vec2> getRandomPositions(int quantity, const Walls& walls) const;

	int getWidth() const;
	int getHeight() const;

private:
	int m_width;
	int m_height;
	int m_wallAmount;
	std::vector<glm::vec2> m_wallOffsets;

	std::unique_ptr<MazeGenerator> m_generator;
};
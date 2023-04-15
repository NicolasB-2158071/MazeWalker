#pragma once

#include "MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"

class Maze
{
public:
	Maze(const glm::mat4& projection);

	// Constructor level
	// Random maze generator (default constructor)

	void draw(Renderer& renderer);

	bool isWallColision(glm::vec2 cameraPos) const;

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls;
	// Models

	// Frequently used data (every player movement)
	const std::vector<glm::vec2>& m_wallsXZLocations;
	glm::vec3 m_wallSize;
};
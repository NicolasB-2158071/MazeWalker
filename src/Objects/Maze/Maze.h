#pragma once

#include "MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"
#include "Lights.h"

class Maze
{
public:
	Maze();

	// Constructor level
	// Random maze generator (default constructor)

	void draw(Renderer& renderer);

	bool isWallColision(const glm::vec2& cameraPos) const;

	Lights& getLights();

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls;
	Lights m_lights;
	// Models

	// Frequently used data (every player movement)
	const std::vector<glm::vec2>& m_wallsXZLocations;
	glm::vec3 m_wallSize;

	const float OFFSET = 0.15f;
};
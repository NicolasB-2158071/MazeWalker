#pragma once

#include "MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"

#include "LightObject.h"

class Maze
{
public:
	Maze();

	// Constructor level
	// Random maze generator (default constructor)

	void draw(Renderer& renderer);

	bool isWallColision(const glm::vec2& cameraPos) const;

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls;
	// Models

	// TEMP
	LightObject m_lightCube;

	// Frequently used data (every player movement)
	const std::vector<glm::vec2>& m_wallsXZLocations;
	glm::vec3 m_wallSize;

	const static int OFFSET = 0.15f;
};
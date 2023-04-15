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

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls; // Collision detection via eventManager
	// Models
};
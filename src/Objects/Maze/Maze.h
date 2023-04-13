#pragma once

#include "Floor.h"
#include "Walls.h"

class Maze
{
public:
	Maze();

	// Constructor level
	// Random maze generator (default constructor)

	void draw(Renderer& renderer);

private:
	Floor m_floor;
	Walls m_walls; // Collision detection via eventManager
	// Models
};
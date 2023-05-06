#pragma once

#include "Generator/MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"
#include "Lights.h"
#include "Masks.h"
#include "BlackHole.h"

class Maze
{
public:
	Maze(EventManager* eventManager);

	void draw(Renderer& renderer);
	bool isCollision(const glm::vec2& cameraPos) const;

	float getMazeWidth() const;
	float getMazeHeight() const;

private:
	MazeBuilder m_builder;
	Walls m_walls;
	Floor m_floor;
	Lights m_lights;
	Masks m_masks;
	BlackHole m_blackHole;
};
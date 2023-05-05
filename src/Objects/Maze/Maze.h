#pragma once

#include "Generator/MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"
#include "Lights.h"
#include "Masks.h"

class Maze
{
public:
	Maze(EventManager* eventManager);

	void draw(Renderer& renderer);
	bool isCollision(const glm::vec2& cameraPos) const;

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls;
	Lights m_lights;
	Masks m_masks;

	sf::Music m_backgroundMusic;
	void initAudio();
};
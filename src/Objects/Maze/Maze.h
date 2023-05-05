#pragma once

#include "Generator/MazeBuilder.h"
#include "Floor.h"
#include "Walls.h"
#include "Lights.h"

class Maze
{
public:
	Maze();

	void draw(Renderer& renderer);
	bool isCollision(const glm::vec2& cameraPos) const;
	Lights& getLights();

private:
	MazeBuilder m_builder;
	Floor m_floor;
	Walls m_walls;
	Lights m_lights;
	// Models

	sf::Music m_backgroundMusic;
	void initAudio();
};
#include "Maze.h"

Maze::Maze(const glm::mat4& projection) : m_builder{ glm::vec3{0.2f, 0.5f, 0.2f } }, m_floor{ projection }, m_walls{ projection }
{
	// Init objects based on wallsize, width and height
	m_builder.readLocations("res/maze.txt");
	m_floor.initObject(m_builder.getWidth(), m_builder.getHeight());
	m_walls.initObject(m_builder.getWallAmount(), m_builder.getWallLocations());
}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
}

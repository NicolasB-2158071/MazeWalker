#include "Maze.h"

Maze::Maze() : m_reader{"res/testMaze.txt"}, m_floor{glm::vec2{1.0f, 1.0f}}, m_walls{glm::vec3{0.1f, 0.5f, 0.1f}, m_reader.getWallAmount(), m_reader.getWallLocations()}
{}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
}

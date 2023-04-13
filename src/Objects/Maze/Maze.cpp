#include "Maze.h"

Maze::Maze() : m_reader{"res/maze.txt"}, m_floor{glm::vec2{1.0f, 1.0f}}, m_walls{glm::vec3{0.01f, 0.5f, 0.01f}, m_reader.getWallAmount(), m_reader.getWallLocations()}
{}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
}

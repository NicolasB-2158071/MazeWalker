#include "Maze.h"

Maze::Maze() : m_floor{ glm::vec2{1.0f, 1.0f} }, m_walls{ glm::vec3{0.2f, 0.5f, 0.2f}, 5} {}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
}

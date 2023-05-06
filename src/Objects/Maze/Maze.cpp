#include "Maze.h"

Maze::Maze(EventManager* eventManager) : /*m_builder{"res/mazes/testMaze.txt"},*/ m_walls{glm::vec3{1.0f, 2.0f, 1.0f}}
{
	// Init objects based on wallsize, width and height
	m_walls.initObject(m_builder.getWallAmount(), m_builder.getWallOffsets());
	m_floor.initObject(getMazeWidth(), getMazeHeight());
	m_blackHole.initObject(getMazeWidth(), getMazeHeight());
	m_lights.setLocations(m_builder.getRandomPositions(Lights::NUMBER_OF_LIGHTS, m_walls));
	m_masks.setLocations(m_builder.getRandomPositions(Masks::NUMBER_OF_MASKS, m_walls));

	m_lights.initLightsInput(eventManager);
	m_masks.initMasksInput(eventManager);
	m_blackHole.initBlackHoleInput(eventManager);
}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
	m_lights.draw(renderer);
	m_masks.draw(renderer);
	m_blackHole.draw(renderer);
}

// Possibility for other collision checking
bool Maze::isCollision(const glm::vec2& cameraPos) const
{
	return m_walls.isWallColision(cameraPos);
}

float Maze::getMazeWidth() const
{
	return m_builder.getWidth() * m_walls.getWallSize().x;
}

float Maze::getMazeHeight() const
{
	return m_builder.getHeight() * m_walls.getWallSize().z;
}

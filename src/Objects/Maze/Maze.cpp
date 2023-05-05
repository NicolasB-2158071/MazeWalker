#include "Maze.h"

Maze::Maze(EventManager* eventManager) : /*m_builder{"res/mazes/maze.txt"},*/ m_walls{glm::vec3{1.0f, 2.0f, 1.0f}}
{
	// Init objects based on wallsize, width and height
	m_floor.initObject(m_builder.getWidth() * m_walls.getWallSize().x, m_builder.getHeight() * m_walls.getWallSize().z);
	m_walls.initObject(m_builder.getWallAmount(), m_builder.getWallOffsets());
	m_lights.setLocations(m_builder.getRandomPositions(Lights::NUMBER_OF_LIGHTS, m_walls));
	m_masks.setLocations(m_builder.getRandomPositions(Masks::NUMBER_OF_MASKS, m_walls));

	m_lights.initLightsInput(eventManager);

	initAudio();
}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
	m_lights.draw(renderer);
	m_masks.draw(renderer);
}

// Possibility for other collision checking
bool Maze::isCollision(const glm::vec2& cameraPos) const
{
	return m_walls.isWallColision(cameraPos);
}

void Maze::initAudio()
{
	if (!m_backgroundMusic.openFromFile("res/Audio/Ambient.wav"))
	{
		std::cout << "ERROR loading background sound";
		return;
	}
	m_backgroundMusic.setPosition(m_builder.getWidth(), 0.5f, m_builder.getHeight());
	m_backgroundMusic.setMinDistance(5.0f);
	m_backgroundMusic.setLoop(true);
	m_backgroundMusic.setVolume(50.0f);
	m_backgroundMusic.play();
}

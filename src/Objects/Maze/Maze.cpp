#include "Maze.h"

Maze::Maze(const glm::mat4& projection) : m_builder{ glm::vec3{1.0f, 1.0f, 1.0f } }, m_floor{ projection }, m_walls{ projection },
m_wallsXZLocations{m_builder.getWallsXZLocations()}, m_wallSize{ m_builder.getWallSize()}
{
	// Init objects based on wallsize, width and height
	m_builder.readLocations("res/maze.txt");
	m_floor.initObject(m_builder.getWidth(), m_builder.getHeight());
	m_walls.initObject(m_builder.getWallAmount(), m_builder.getWallsLocationMatrices());
}

void Maze::draw(Renderer& renderer)
{
	m_floor.draw(renderer);
	m_walls.draw(renderer);
}

bool Maze::isWallColision(const glm::vec2& cameraPos) const
{
	for (auto& pos : m_wallsXZLocations)
	{
		// Between x and z intervals (pos is origin of object)
		/*bool collisionX{ pos.x - m_wallSize.x - OFFSET < cameraPos.x && cameraPos.x < pos.x + m_wallSize.x + OFFSET };
		bool collisionZ{ pos.y - m_wallSize.z - OFFSET < cameraPos.y && cameraPos.y < pos.y + m_wallSize.z + OFFSET };*/
		bool collisionX{ pos.x - OFFSET < cameraPos.x && cameraPos.x < pos.x + m_wallSize.x + OFFSET };
		bool collisionZ{ pos.y - OFFSET < cameraPos.y && cameraPos.y < pos.y + m_wallSize.z + OFFSET };
		if (collisionX && collisionZ)
			return true;
	}
	return false;
}

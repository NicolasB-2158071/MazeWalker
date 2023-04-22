#include "MazeBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

MazeBuilder::MazeBuilder(const glm::vec3& wallSize) : m_wallAmount{}, m_width{}, m_height{}, m_wallSize{ wallSize } {}

void MazeBuilder::readLocations(const char* mazePath)
{
	std::ifstream stream(mazePath);
	std::string line;

	stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	int xOffset = 0, zOffset = 0;
	m_width = 0, m_height = 0, m_wallAmount = 0;
	try {
		while (stream.good())
		{
			std::getline(stream, line);
			for (char c : line)
			{
				if (c == '#')
				{
					m_wallLocatioMatrices.push_back(calculateModel(xOffset, zOffset));
					m_wallsXZLocations.push_back(glm::vec2{ xOffset * m_wallSize.x, zOffset * m_wallSize.z});
					++m_wallAmount;
				}
				++xOffset;
			}
			m_width = xOffset;
			xOffset = 0;
			++zOffset;
		}
		m_height = zOffset;
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::MAZE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
}

std::vector<glm::mat4>& MazeBuilder::getWallsLocationMatrices()
{
	return m_wallLocatioMatrices;
}

const std::vector<glm::vec2>& MazeBuilder::getWallsXZLocations() const
{
	return m_wallsXZLocations;
}

glm::vec3 MazeBuilder::getWallSize() const
{
	return m_wallSize;
}

int MazeBuilder::getWallAmount() const
{
	return m_wallAmount;
}

std::vector<glm::vec2> MazeBuilder::getRandomLightPositions(int quantity) const
{
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	std::vector<glm::vec2> lightLocations;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> disWidth(0, getWidth());
	std::uniform_real_distribution<> disHeight(0, getHeight());

	while (quantity > 0)
	{
		glm::vec2 location{ disWidth(gen), disHeight(gen) };
		if (!isWall(location))
		{
			lightLocations.push_back(location);
			--quantity;
		}
	}

	return lightLocations;
}

float MazeBuilder::getWidth() const
{
	return m_width * m_wallSize.x;
}

float MazeBuilder::getHeight() const
{
	return m_height * m_wallSize.z;
}

glm::mat4 MazeBuilder::calculateModel(int xOffset, int zOffset) const
{
	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3{ m_wallSize.x * xOffset, 0, m_wallSize.z * zOffset });
	model = glm::scale(model, glm::vec3{ m_wallSize.x, m_wallSize.y, m_wallSize.z});

	return std::move(model);
}

// Code duplicatie!!!
bool MazeBuilder::isWall(const glm::vec2& location) const
{
	int OFFSET = 0.15f;
	for (auto& wallLocations : m_wallsXZLocations)
	{
		// Between x and z intervals (pos is origin of object)
		bool collisionX{ wallLocations.x - OFFSET < location.x && location.x < wallLocations.x + m_wallSize.x + OFFSET };
		bool collisionZ{ wallLocations.y - OFFSET < location.y && location.y < wallLocations.y + m_wallSize.z + OFFSET };
		if (collisionX && collisionZ)
			return true;
	}
	return false;
}

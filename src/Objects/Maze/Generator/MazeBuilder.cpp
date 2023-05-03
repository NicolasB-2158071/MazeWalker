#include "MazeBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>


// File meekrijg of niet (nullptr checken)
MazeBuilder::MazeBuilder(const glm::vec3& wallSize, const char* mazeFile) : m_wallAmount{}, m_width{}, m_height{}, m_wallSize{ wallSize }, m_generator{ std::make_unique<PrimGenerator>() }
{
	if (mazeFile != nullptr)
		readLocations(mazeFile); // width, height, wallamount also in this function
	else
	{
		int tileWidth = 10, tileHeight = 15;
		m_generator->generateMaze(tileWidth, tileHeight);
		m_wallOffsets = m_generator->getWallLocations();
		m_wallAmount = m_wallOffsets.size();
		m_width = tileWidth * 2 - 1, m_height = tileHeight * 2 - 1;
	}
	calculateXZLocations();
	calculateLocationMatrices();
}

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
					m_wallOffsets.push_back(glm::vec2{ xOffset, zOffset });
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
	return m_wallLocationMatrices;
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

	while (quantity > 1)
	{
		glm::vec2 location{ disWidth(gen), disHeight(gen) };
		if (!isWall(location))
		{
			lightLocations.push_back(location);
			--quantity;
		}
	}
	lightLocations.push_back(glm::vec2{ getWidth() - (m_wallSize.x / 2), getHeight() - (m_wallSize.y / 2)}); // Finish light
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

void MazeBuilder::calculateXZLocations()
{
	for (auto& offset : m_wallOffsets)
		m_wallsXZLocations.push_back(glm::vec2{ offset.x * m_wallSize.x, offset.y * m_wallSize.z });
}

void MazeBuilder::calculateLocationMatrices()
{
	for (auto& offset : m_wallOffsets)
		m_wallLocationMatrices.push_back(calculateModel(offset.x, offset.y));
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


// Enkel x, z offsets
// -> wallXZLocaties berekenen
// -> WallLocationMatrices berekenen
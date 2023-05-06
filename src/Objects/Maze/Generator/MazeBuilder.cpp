#include "MazeBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../../../Util/RandomGenerator.h"


// File meekrijg of niet (nullptr checken)
MazeBuilder::MazeBuilder(const char* mazeFile) : m_wallAmount{}, m_width{}, m_height{}, m_generator{ std::make_unique<PrimGenerator>() }
{
	if (mazeFile != nullptr)
		readLocations(mazeFile); // width, height, wallamount also in this function
	else
	{
		int tileWidth = 8, tileHeight = 15;
		m_generator->generateMaze(tileWidth, tileHeight);
		m_wallOffsets = m_generator->getWallLocations();
		m_wallAmount = m_wallOffsets.size();
		m_width = tileWidth * 2 - 1, m_height = tileHeight * 2 - 1;
	}
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

const std::vector<glm::vec2>& MazeBuilder::getWallOffsets() const
{
	return m_wallOffsets;
}

int MazeBuilder::getWallAmount() const
{
	return m_wallAmount;
}

std::vector<glm::vec2> MazeBuilder::getRandomPositions(int quantity, const Walls& walls) const
{
	std::vector<glm::vec2> positions;

	float maxWidth{ getWidth() * walls.getWallSize().x };
	float maxHeight{ getHeight() * walls.getWallSize().z };

	while (quantity > 0)
	{
		glm::vec2 position{ RandomGenerator::randomFloat(0, maxWidth), RandomGenerator::randomFloat(0, maxHeight) };
		if (!walls.isWallColision(position))
		{
			positions.push_back(position);
			--quantity;
		}
	}
	return positions;
}

int MazeBuilder::getWidth() const
{
	return m_width;
}

int MazeBuilder::getHeight() const
{
	return m_height;
}
#include "MazeBuilder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

glm::mat4* MazeBuilder::getWallsLocationMatrices()
{
	return m_wallLocatioMatrices.data();
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

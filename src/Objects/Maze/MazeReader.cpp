#include "MazeReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

MazeReader::MazeReader(const char* mazePath) : m_wallAmount{}
{
	readLocations(mazePath);
}

void MazeReader::readLocations(const char* mazePath)
{
	std::ifstream stream(mazePath);
	std::string line;

	stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	int xOffset = 0, zOffset = 0;
	try {
		while (stream.good())
		{
			std::getline(stream, line);
			for (char c : line)
			{
				if (c == '#')
				{
					m_wallLocations.push_back(glm::vec2{xOffset, zOffset});
					++m_wallAmount;
				}
				++xOffset;
			}
			xOffset = 0.;
			++zOffset;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::MAZE::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
}

glm::vec2* MazeReader::getWallLocations()
{
	return m_wallLocations.data();
}

int MazeReader::getWallAmount() const
{
	return m_wallAmount;
}

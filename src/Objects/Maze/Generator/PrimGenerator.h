#pragma once

#include "MazeGenerator.h"
#include "Cell.h"

class PrimGenerator : public MazeGenerator
{
public:

	// https://cantwell-tom.medium.com/prims-algorithm-as-a-maze-in-javascript-aec7415ad2cd
	void generateMaze(int width, int height) override;
	std::vector<glm::vec2> getWallLocations() const override;

private:

	int m_width;
	int m_height;

	std::vector<std::vector<Cell>> m_cells;
	std::vector<glm::vec2> m_wallLocations;

	std::vector<glm::vec2> m_visited;
	std::vector<glm::vec2> m_frontier;

	void initCells(int width, int height);
	void collectWalls();
	void removeWallsBetweenCells(const glm::vec2& cellOne, const glm::vec2& cellTwo);

	bool inBounds(int x, int y) const;
	bool isNeighbour(const glm::vec2& cell, const glm::vec2& neighbour) const;
	bool inFrontier(int x, int y) const;

	glm::vec2 removeRandomFrontierCell();
	void addCellsToFrontier(const glm::vec2& currentCell);
	glm::vec2 getNeighbourCellInVisited(const glm::vec2& currentCell) const;
};
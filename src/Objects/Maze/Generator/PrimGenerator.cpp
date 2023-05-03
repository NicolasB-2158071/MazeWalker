#include "PrimGenerator.h"

void PrimGenerator::generateMaze(int width, int height)
{
	srand(time(0));
	initCells(width, height);
	m_visited.clear();
	m_frontier.clear();

	// Starting point
	m_visited.push_back(glm::vec2{0, 0});
	m_cells[0][0].visited = true;
	addCellsToFrontier(m_visited[0]);

	// Main loop
	while (!m_frontier.empty())
	{
		glm::vec2 currentCell{ removeRandomFrontierCell() }; // Remove from frontier
		m_visited.push_back(currentCell); // Add to visited
		m_cells[currentCell.y][currentCell.x].visited = true;
		
		glm::vec2 neighBour{ getNeighbourCellInVisited(currentCell) }; // Get a neighbour in visited
		removeWallsBetweenCells(currentCell, neighBour); // Remove walls between the two

		addCellsToFrontier(currentCell); // Add frontier cells of current cell
	}
	collectWalls();
}

std::vector<glm::vec2> PrimGenerator::getWallLocations() const
{
	return m_wallLocations;
}

void PrimGenerator::initCells(int width, int height)
{
	m_width = width, m_height = height;

	m_cells.clear();
	for (int i = 0; i < height; ++i)
	{
		m_cells.push_back(std::vector<Cell>{});
		for (int j = 0; j < width; ++j)
			m_cells[i].push_back(Cell{});
	}
}

void PrimGenerator::collectWalls()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			if (m_cells[i][j].wallLeft)
				m_wallLocations.push_back(glm::vec2{ 2 * j - 1, 2 * i });

			if (m_cells[i][j].wallTop)
				m_wallLocations.push_back(glm::vec2{ 2 * j, 2 * i - 1 });

			m_wallLocations.push_back(glm::vec2{ 2 * j - 1, 2 * i - 1 }); // Left top
		}
		// Last one also right wall
		m_wallLocations.push_back(glm::vec2{ 2 * m_width - 1, 2 * i }); // Right
		m_wallLocations.push_back(glm::vec2{ 2 * m_width - 1, 2 * i - 1 }); // Right top
	}
	// Last row bottom walls
	for (int i = -1; i < m_width * 2; ++i)
		m_wallLocations.push_back(glm::vec2{i , 2 * m_height - 1 });
}

void PrimGenerator::removeWallsBetweenCells(const glm::vec2& cellOne, const glm::vec2& cellTwo)
{
	// cellOne left cellTwo
	if (cellOne.x == cellTwo.x - 1 && cellOne.y == cellTwo.y)
	{
		m_cells[cellOne.y][cellOne.x].wallRight = false;
		m_cells[cellTwo.y][cellTwo.x].wallLeft = false;
		return;
	}

	// cellOne top cellTwo
	if (cellOne.x == cellTwo.x && cellOne.y == cellTwo.y - 1)
	{
		m_cells[cellOne.y][cellOne.x].wallBottom = false;
		m_cells[cellTwo.y][cellTwo.x].wallTop = false;
		return;
	}

	// cellOne right cellTwo
	if (cellOne.x == cellTwo.x + 1 && cellOne.y == cellTwo.y)
	{
		m_cells[cellOne.y][cellOne.x].wallLeft = false;
		m_cells[cellTwo.y][cellTwo.x].wallRight = false;
		return;
	}

	// cellOne bottom cellTwo
	if (cellOne.x == cellTwo.x && cellOne.y == cellTwo.y + 1)
	{
		m_cells[cellOne.y][cellOne.x].wallTop = false;
		m_cells[cellTwo.y][cellTwo.x].wallBottom = false;
		return;
	}
}

// y is row, x is column
bool PrimGenerator::inBounds(int x, int y) const
{
	return ((- 1 < y && y < m_height) && (-1 < x && x < m_width));
}

bool PrimGenerator::isNeighbour(const glm::vec2& cell, const glm::vec2& neighbour) const
{
	// Neighbour is left
	if (cell.x == neighbour.x + 1 && cell.y == neighbour.y)
		return true;

	// Neighbour is top
	if (cell.x == neighbour.x && cell.y == neighbour.y + 1)
		return true;

	// Neighbour is right
	if (cell.x == neighbour.x - 1 && cell.y == neighbour.y)
		return true;

	// Neighbour is bottom
	if (cell.x == neighbour.x && cell.y == neighbour.y - 1)
		return true;

	return false;
}

bool PrimGenerator::inFrontier(int x, int y) const
{
	for (auto& cell : m_frontier)
		if (cell.x == x && cell.y == y)
			return true;
	return false;
}

glm::vec2 PrimGenerator::removeRandomFrontierCell()
{
	int randomIndex{ static_cast<int>(rand() % m_frontier.size()) };
	glm::vec2 ret{ m_frontier[randomIndex] };
	m_frontier.erase(m_frontier.begin() + randomIndex);
	return ret;
}

void PrimGenerator::addCellsToFrontier(const glm::vec2& currentCell)
{
	int x = currentCell.x;
	int y = currentCell.y;

	// Left
	if (inBounds(x - 1, y) && !m_cells[y][x - 1].visited && !inFrontier(x - 1, y))
		m_frontier.push_back(glm::vec2{ x - 1, y });

	// Top
	if (inBounds(x, y - 1) && !m_cells[y - 1][x].visited && !inFrontier(x, y - 1))
		m_frontier.push_back(glm::vec2{ x, y - 1 });

	// Right
	if (inBounds(x + 1, y) && !m_cells[y][x + 1].visited && !inFrontier(x + 1, y))
		m_frontier.push_back(glm::vec2{ x + 1, y });

	// Bottom
	if (inBounds(x, y + 1) && !m_cells[y + 1][x].visited && !inFrontier(x, y + 1))
		m_frontier.push_back(glm::vec2{ x, y + 1 });
}

glm::vec2 PrimGenerator::getNeighbourCellInVisited(const glm::vec2& currentCell) const
{
	std::vector<glm::vec2> temp;
	for (auto& cell : m_visited)
		if (isNeighbour(currentCell, cell))
			temp.push_back(cell);

	return temp[static_cast<int>(rand() % temp.size())];
}

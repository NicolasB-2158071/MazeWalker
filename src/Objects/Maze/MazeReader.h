#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class MazeReader
{
public:
	MazeReader(const char* mazePath);

	void readLocations(const char* mazePath);

	glm::vec2* getWallLocations();
	int getWallAmount() const;

	// x en z richting
	// # found -> glm::vec2
	// ++amount

	// Wall size (zelfde x en z)

	// Weten waar player start voor vloor ook te tekenen en translatie muren

private:
	int m_wallAmount;
	std::vector<glm::vec2> m_wallLocations;

};
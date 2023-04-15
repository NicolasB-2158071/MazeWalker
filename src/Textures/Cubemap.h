#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

class Cubemap
{
public:
	Cubemap(const std::vector<std::string>& textures, unsigned int rgbType);
	~Cubemap();

	void activeAndBind(unsigned int slot) const;
	void unbind() const;

private:
	unsigned int m_cubemapID;

	void loadImage(const char* path, unsigned int rgbType, int pos);
};
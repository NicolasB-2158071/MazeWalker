#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(const char* path, unsigned int rgbType);
	~Texture();

	void activeAndBind(unsigned int slot) const;
	void unbind() const;

private:
	unsigned int m_textureID;

	int m_textureWidth;
	int m_textureHeight;
	int m_nrChannels;
	void loadImage(const char* path, unsigned int rgbType);
};
#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(const char* path, bool copied = false);
	~Texture();


	void activeAndBind(unsigned int slot) const;
	void unbind() const;

private:
	unsigned int m_textureID;
	int m_textureWidth;
	int m_textureHeight;
	int m_nrChannels;

	bool m_delete = true; // Hacky solution but relative fast, copy and move constructor turned out to be very slow
	void loadImage(const char* path);
};
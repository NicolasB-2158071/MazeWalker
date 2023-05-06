#include "Cubemap.h"

#include <iostream>
#include "../stb_image.h"

Cubemap::Cubemap(const std::vector<std::string>& textures)
{
	glGenTextures(1, &m_cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < textures.size(); ++i)
		loadImage(textures[i].c_str(), i);
}

Cubemap::~Cubemap()
{
	glDeleteTextures(1, &m_cubemapID);
}

void Cubemap::activeAndBind(unsigned int slot) const
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapID);
}

void Cubemap::unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::loadImage(const char* path, int pos)
{
	stbi_set_flip_vertically_on_load(false);
	int textureWidth, textureHeight, nrChannels;
	unsigned char* data{ stbi_load(path, &textureWidth, &textureHeight, &nrChannels, 0) };
	if (data)
	{
		// From learnOpenGL.com model loading
		GLenum format;
		switch (nrChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGB;
			break;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + pos, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load cubemap" << std::endl;
	}
	stbi_image_free(data);
}

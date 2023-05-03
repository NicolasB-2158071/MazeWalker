#include "Texture.h"

#include <iostream>
#include "../../stb_image.h"


Texture::Texture(const char* path, bool copied) : m_delete{ !copied }
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Outside bounds of texture coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Rasterization of texture coordinate
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	loadImage(path);
}

Texture::~Texture()
{
	if (m_delete)
		glDeleteTextures(1, &m_textureID);
}

void Texture::activeAndBind(unsigned int slot) const
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadImage(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data{ stbi_load(path, &m_textureWidth, &m_textureHeight, &m_nrChannels, 0) };
	if (data)
	{
		// From learnOpenGL.com model loading
		GLenum format;
		switch (m_nrChannels)
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

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_textureWidth, m_textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

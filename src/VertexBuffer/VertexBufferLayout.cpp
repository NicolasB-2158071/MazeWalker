#include "VertexBufferLayout.h"
#include <glad/glad.h>

VertexBufferLayout::VertexBufferLayout() : m_stride{} {}

void VertexBufferLayout::addAttribute(unsigned int quantity, unsigned int type, unsigned char normalised)
{
	m_attributes.push_back(BufferAttribute{ quantity, type, normalised });
	m_stride += getSizeOfType(type) * quantity;
}

unsigned int VertexBufferLayout::getStride() const
{
	return m_stride;
}

int VertexBufferLayout::getQuantity() const
{
	return m_attributes.size();
}

BufferAttribute VertexBufferLayout::getItem(int pos) const
{
	return m_attributes[pos];
}

unsigned int VertexBufferLayout::getSizeOfType(unsigned int type) const
{
	switch (type)
	{
	case GL_FLOAT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	case GL_UNSIGNED_BYTE:
		return 1;
	default:
		return 0;
	}
}

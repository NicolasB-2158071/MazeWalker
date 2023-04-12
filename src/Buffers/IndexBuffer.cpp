#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_indexID);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
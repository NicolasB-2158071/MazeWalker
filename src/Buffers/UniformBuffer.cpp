#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(unsigned int size, int bindingPoint)
{
	glGenBuffers(1, &m_uniformID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformID);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW); // reserve data
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, m_uniformID, 0, size); // bind to point
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_uniformID);
}

// Assume already bind
void UniformBuffer::addData(unsigned int offset, unsigned int size, const void* data)
{
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UniformBuffer::bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformID);
}

void UniformBuffer::unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

#pragma once

#include <glad/glad.h>

class UniformBuffer
{
public:
	UniformBuffer(unsigned int size, int bindingPoint);
	~UniformBuffer();

	void addData(unsigned int offset, unsigned int size, const void* data);

	void bind() const;
	void unbind() const;
	
private:
	unsigned int m_uniformID;
};
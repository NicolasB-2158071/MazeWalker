#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

private:
	unsigned int m_indexID;

};
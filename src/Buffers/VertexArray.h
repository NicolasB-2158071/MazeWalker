#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

// Based on: https://www.youtube.com/watch?v=oD1dvfbyf6A&t=529s
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void connectVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vbl) const;
	void connectInstanceBuffer(const VertexBuffer& ivbo, const BufferAttribute& attribute, int beginLocation, int endLocation, size_t sizeOfAttribute) const;

	void bind() const;
	void unbind() const;

private:
	unsigned int m_arrayID;
};
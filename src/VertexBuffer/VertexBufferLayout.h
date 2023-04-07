#pragma once

#include <vector>

struct BufferAttribute
{
	unsigned int quantity;
	unsigned int type;
	unsigned char normalised;
};

// Based on: https://www.youtube.com/watch?v=oD1dvfbyf6A&t=529s
class VertexBufferLayout
{
public:
	VertexBufferLayout();

	void addAttribute(unsigned int quantity, unsigned int type, unsigned char normalised);

	int getQuantity() const;
	BufferAttribute getItem(int pos) const;

	unsigned int getStride() const;
	unsigned int getSizeOfType(unsigned int type) const;

private:
	std::vector<BufferAttribute> m_attributes;
	unsigned int m_stride;
};
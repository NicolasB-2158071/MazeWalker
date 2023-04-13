#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_arrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_arrayID);
}

void VertexArray::connectVertexBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vbl) const
{
	bind();
	vbo.bind();

	// enable layout
	unsigned int stride{ vbl.getStride() };
	unsigned int offset{};
	for (int i = 0; i < vbl.getQuantity(); ++i)
	{
		BufferAttribute attribute{ vbl.getItem(i) };
		
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribute.quantity, attribute.type, attribute.normalised, stride, (void*) offset);
		offset += vbl.getSizeOfType(attribute.type) * attribute.quantity;
	}

	//unbind();
	//vbo.unbind();
}

void VertexArray::connectInstanceBuffer(const VertexBuffer& ivbo, const BufferAttribute& attribute, int location) const
{
	ivbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, attribute.quantity, attribute.type, attribute.normalised, 0, 0); // Tightly packed
	glVertexAttribDivisor(location, 1); // Update attribute every instance
}

void VertexArray::bind() const
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
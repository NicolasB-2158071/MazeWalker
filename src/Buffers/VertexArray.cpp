#include "VertexArray.h"

VertexArray::VertexArray(bool copied) : m_delete{ !copied }
{
	glGenVertexArrays(1, &m_arrayID);
}

VertexArray::~VertexArray()
{
	if (m_delete)
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
		glVertexAttribPointer(i, attribute.quantity, attribute.type, attribute.normalised, stride, (void*)offset);
		offset += vbl.getSizeOfType(attribute.type) * attribute.quantity;
	}

	//unbind();
	//vbo.unbind();
}

// One attribute, the same for every attribute in vertex
void VertexArray::connectInstanceBuffer(const VertexBuffer& ivbo, const BufferAttribute& attribute, int beginLocation, int endLocation, size_t sizeOfAttribute) const // moet?
{
	ivbo.bind();
	for (int i = beginLocation; i <= endLocation; ++i)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attribute.quantity, attribute.type, attribute.normalised, sizeOfAttribute * (1 + endLocation - beginLocation), (void*)(sizeOfAttribute * (i - beginLocation)));
		glVertexAttribDivisor(i, 1); // Update attribute every instance
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_arrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
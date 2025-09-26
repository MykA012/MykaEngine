#include "IndexBuffer.h"

GL_Classes::IndexBuffer::IndexBuffer() : ID(0)
{
	glGenBuffers(1, &ID);
	this->Bind();
}

GL_Classes::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
	this->Unbind();
}

void GL_Classes::IndexBuffer::BufferData(GLsizeiptr size, GLfloat* data)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void GL_Classes::IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GL_Classes::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
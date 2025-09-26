#include "VertexBuffer.h"

GL_Classes::VertexBuffer::VertexBuffer() : ID(0)
{
	glGenBuffers(1, &ID);
	this->Bind();
}

GL_Classes::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
	this->Unbind();
}

void GL_Classes::VertexBuffer::BufferData(GLsizeiptr size, GLfloat* vertices)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GL_Classes::VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GL_Classes::VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_Classes::VertexBuffer::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	this->Bind();

	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);

	this->Unbind();
}

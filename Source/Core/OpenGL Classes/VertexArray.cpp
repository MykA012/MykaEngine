#include "VertexArray.h"

GL_Classes::VertexArray::VertexArray() : ID(0)
{
	glGenVertexArrays(1, &ID);
}

GL_Classes::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
	this->Unbind();
}


void GL_Classes::VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void GL_Classes::VertexArray::Unbind()
{
	glBindVertexArray(0);
}
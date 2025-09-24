#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>

namespace GL_Classes
{
	using namespace std;

	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void BufferData(GLsizeiptr size, GLfloat* vertices);
		void Bind();
		void Unbind();
		void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

	private:
		GLuint ID;
	};
}
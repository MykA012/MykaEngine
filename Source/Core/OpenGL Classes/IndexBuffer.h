#pragma once

#include <glad/glad.h>

namespace GL_Classes
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void BufferData(GLsizeiptr size, GLfloat* data);
		void Bind();
		void Unbind();

	private:
		GLuint ID;
	};
}


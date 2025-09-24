#include "Shader.h"

GL_Classes::Shader::Shader(const string vertexPath, const string fragmentPath) : m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
{
	this->m_VertexData = getFileContent(vertexPath);
	this->m_FragmentData = getFileContent(fragmentPath);
}

GL_Classes::Shader::~Shader()
{
	glUseProgram(0);
}

void GL_Classes::Shader::CompileShaders()
{
	GLuint vs;
	GLuint fs;
	GLint successful;
	GLchar GLInfoLog[512];

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs_char = m_VertexData.c_str();
	const char* fs_char = m_FragmentData.c_str();

	glShaderSource(vs, 1, &vs_char, 0);
	glShaderSource(fs, 1, &fs_char, 0);

	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &successful);

	if (!successful)
	{
		glGetShaderInfoLog(vs, 512, NULL, GLInfoLog);
		std::cout << "\nCOMPILATION ERROR IN VERTEX SHADER (" << m_VertexPath << ")" << "\n" << GLInfoLog << "\n\n";
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &successful);

	if (!successful)
	{
		glGetShaderInfoLog(fs, 512, NULL, GLInfoLog);
		std::cout << "\nCOMPILATION ERROR IN FRAGMENT SHADER (" << m_FragmentPath << ")" << "\n" << GLInfoLog << "\n";
	}

	m_Program = glCreateProgram();
	glAttachShader(m_Program, vs);
	glAttachShader(m_Program, fs);
	glLinkProgram(m_Program);

	glGetProgramiv(m_Program, GL_LINK_STATUS, &successful);

	if (!successful)
	{
		glGetProgramInfoLog(m_Program, 512, NULL, GLInfoLog);
		std::cout << "ERROR : SHADER LINKING FAILED : \n" << GLInfoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void GL_Classes::Shader::Use()
{
	glUseProgram(m_Program);
}

GLuint GL_Classes::Shader::getProgramID() const
{
	return m_Program;
}

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace GL_Classes
{
	using namespace std;


	class Shader
	{
	public:
		Shader(const string vertexPath, const string fragmentPath);

		~Shader();

		void CompileShaders();
		void Use();

		GLuint getProgramID() const;

	private:
		GLuint m_Program;

		string m_VertexPath;
		string m_FragmentPath;
		string m_VertexData;
		string m_FragmentData;

		string getFileContent(const string path)
		{
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				shaderFile.open(path);
				std::stringstream shaderStream;
				shaderStream << shaderFile.rdbuf();
				shaderFile.close();
				return shaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
				return "";
			}
		}
	};
}
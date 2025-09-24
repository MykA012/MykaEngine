#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL Classes/VertexBuffer.h"
#include "OpenGL Classes/VertexArray.h"
#include "OpenGL Classes/Shader.h"


using namespace GL_Classes;

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void RenderCube(const glm::vec3& position, float rotation, const glm::mat4& projection, const glm::mat4& view, Shader* shader);

private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	Shader m_DefaultShader;
};
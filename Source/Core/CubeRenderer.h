#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGL Classes/VertexBuffer.h"
#include "OpenGL Classes/VertexArray.h"
#include "OpenGL Classes/IndexBuffer.h"
#include "OpenGL Classes/Shader.h"
#include "OpenGL Classes/Texture.h"


using namespace GL_Classes;

class CubeRenderer
{
public:
	CubeRenderer();
	~CubeRenderer();

	void RenderCube(const glm::vec3& position, Texture& texture, float rotation, const glm::mat4& projection, const glm::mat4& view, Shader* shader);

private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
	Shader m_DefaultShader;
};
#include "CubeRenderer.h"

CubeRenderer::CubeRenderer() : m_DefaultShader(Shader::SHADERS_DIR + "CubeRendererVert.glsl", Shader::SHADERS_DIR + "CubeRendererFrag.glsl")
{
	m_DefaultShader.CompileShaders();

	GLfloat vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		// back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		// right
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		 // left
		 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		 // top
		 -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		 -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		 // bottom
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f
	};

	m_VAO.Bind();

	m_VBO.BufferData(sizeof(vertices), vertices);
	m_VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	m_VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	m_VAO.Unbind();
}

CubeRenderer::~CubeRenderer() {}

void CubeRenderer::RenderCube(const glm::vec3& position, float rotation, const glm::mat4& projection, const glm::mat4& view, Shader* shader)
{
	Shader* useShader;

	if (shader == nullptr)
	{
		useShader = &m_DefaultShader;
	}
	else
	{
		useShader = shader;
	}

	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.5f, 0.5f));

	//glm::mat4 view = glm::mat4(1.0f);
	//glm::mat4 proj = glm::mat4(1.0f);

	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);


	useShader->Use();
	useShader->SetMatrix4("model", model);
	useShader->SetMatrix4("view", view);
	useShader->SetMatrix4("projection", projection);


	m_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_VAO.Unbind();
}



#include "TriangleRenderer.h"

Shapes::TriangleRenderer::TriangleRenderer() : m_DefaultShader(SHADERS_DIR + "vertex.glsl", SHADERS_DIR + "fragment.glsl")
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

Shapes::TriangleRenderer::~TriangleRenderer() {}

void Shapes::TriangleRenderer::RenderTriangle(/*glm::vec3& position, */float rotation/*, const glm::mat4& projection, const glm::mat4& view*/, Shader* shader)
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

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 2.0f, 2.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(useShader->getProgramID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(useShader->getProgramID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	int projLoc = glGetUniformLocation(useShader->getProgramID(), "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	useShader->Use();

	m_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_VAO.Unbind();
}



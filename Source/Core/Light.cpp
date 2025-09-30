#include "Light.h"

Light::Light() : m_DefaultShader(Shader::SHADERS_DIR + "lightVert.glsl", Shader::SHADERS_DIR + "lightFrag.glsl")
{
	m_DefaultShader.CompileShaders();

	GLfloat vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
							
		-0.5f, -0.5f,  0.5f, 
		 0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f, 
							
		// back				
		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
							
		-0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f, 
						
		// right			
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
							
		 0.5f, -0.5f, -0.5f, 
		 0.5f,  0.5f,  0.5f, 
		 0.5f, -0.5f,  0.5f, 

		 // left
		 -0.5f, -0.5f, -0.5f,
		 -0.5f,  0.5f, -0.5f,
		 -0.5f,  0.5f,  0.5f,
					
		 -0.5f, -0.5f, -0.5f,
		 -0.5f,  0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f,
						
		 // top			
		 -0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f,  0.5f,
					
		 -0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f,  0.5f,
		 -0.5f,  0.5f,  0.5f,
						
		 // bottom			
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
						
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f
	};

	m_VAO.Bind();

	m_VBO.BufferData(sizeof(vertices), vertices);
	m_VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	m_VAO.Unbind();
}

void Light::RenderLight(const glm::vec3& position, glm::vec4 color, const glm::mat4& projection, const glm::mat4& view, Shader* shader)
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
	//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

	useShader->Use();
	useShader->SetVector4f("color", color);
	useShader->SetMatrix4("model", model);
	useShader->SetMatrix4("view", view);
	useShader->SetMatrix4("projection", projection);

	m_VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_VAO.Unbind();
}

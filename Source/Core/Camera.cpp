#include "Camera.h"

Camera::Camera(int width, int height, const glm::vec3& position) : m_Width(width), m_Height(height), m_Position(position)
{
	UpdateMatrices(45.0f, 0.1f, 100.f);
}

void Camera::UpdateMatrices(float fov, float zNear, float zFar)
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

	m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)m_Width / (float)m_Height, zNear, zFar);
}

const glm::mat4& Camera::GetViewMatrix() const { return m_ViewMatrix; }

const glm::mat4& Camera::GetProjectionMatrix() const { return m_ProjectionMatrix; }

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	float speed = m_Velocity * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += speed * m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += speed * -glm::normalize(glm::cross(m_Front, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += speed * -m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += speed * glm::normalize(glm::cross(m_Front, m_Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += speed * -m_Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Velocity = 0.1f * 3.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Velocity = 0.1f;
	}
}

#include "Core/CubeRenderer.h"

float width = 800;
float height = 600;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	

	CubeRenderer cubeRenderer;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// make transparent
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			glEnable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
		{
			glDisable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0 / 60)
		{
			rotation += 1.0f;
			prevTime = crntTime;
		}

		glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
		float FOV = glm::radians(100.0f);

		float RenderDistanceNear = 0.1f;
		float RenderDistanceFar = 100.0f;

		cubeRenderer.RenderCube(position, rotation, glm::perspective(FOV, width / height, RenderDistanceNear, RenderDistanceFar), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
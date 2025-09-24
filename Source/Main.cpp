#include "Core/CubeRenderer.h"

const unsigned int width = 800;
const unsigned int height = 600;

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

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0 / 60)
		{
			rotation += 1.0f;
			prevTime = crntTime;
		}

		cubeRenderer.RenderCube(rotation, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#include "Core/CubeRenderer.h"
#include "Core/Camera.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800;
	int height = 600;
	int transparentKey = GLFW_KEY_T;

	GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	float rotation = 0.0f;
	float deltaTime = 0.0f;
	float prevTime = 0.0f;

	glEnable(GL_DEPTH_TEST);
	
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	CubeRenderer cubeRenderer;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// make transparent
		if (glfwGetKey(window, transparentKey) == GLFW_PRESS)
		{
			glEnable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (glfwGetKey(window, transparentKey) == GLFW_RELEASE)
		{
			glDisable(GL_POLYGON_SMOOTH);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0 / 60)
		{
			rotation += 1.0f;
			deltaTime = crntTime - prevTime;
			prevTime = crntTime;
		}

		camera.Inputs(window, deltaTime);
		camera.UpdateMatrices(45.0f, 0.1f, 10000.0f);

		cubeRenderer.RenderCube(glm::vec3(0.0f, 0.0f, -3.0f), rotation, camera.GetProjectionMatrix(), camera.GetViewMatrix(), nullptr);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
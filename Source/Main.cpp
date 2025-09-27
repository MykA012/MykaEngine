#include "Core/CubeRenderer.h"
#include "Core/Camera.h"

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 1920;
	int height = 1080;
	int transparentKey = GLFW_KEY_T;

	GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	// Rotation vars
	float rotation = 0.0f;
	float deltaTime = 0.0f;
	float prevTime = 0.0f;

	glEnable(GL_DEPTH_TEST);
	
	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 2.0f, 5.0f));

	// Renderer
	CubeRenderer cubeRenderer;

	// Textures
	Texture brick("C:/Users/Vova/source/repos/MykaEngine/Source/Resources/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture grass_block("C:/Users/Vova/source/repos/MykaEngine/Source/Resources/grass_block.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

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
		camera.UpdateMatrices(45.0f, 0.1f, 100.0f);

		for (float i = 0.0f; i < 50; i += 1.0f)
		{
			for (float j = 0.0f; j < 50; j += 1.0f)
			{
				cubeRenderer.RenderCube(glm::vec3(i, 0.0f, j), brick, 0, camera.GetProjectionMatrix(), camera.GetViewMatrix(), nullptr);
			}
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
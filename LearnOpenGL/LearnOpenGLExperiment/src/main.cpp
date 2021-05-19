//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Needed on MacOSX
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	constexpr int startingWidth{ 800 };
	constexpr int startingHeight{ 600 };
	GLFWwindow* window = glfwCreateWindow(startingWidth, startingHeight, "LearnOpenGLExperiment", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, startingWidth, startingHeight);

	//Using a lambda as the resize function for the callback
	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//Rendering
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
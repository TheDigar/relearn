#include "OpenGLContext.h"

//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

OpenGLContext::OpenGLContext(int width, int height):
	mWidth{ width }, mHeight {height}
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	mWindow = glfwCreateWindow(mWidth, mHeight, "LearnOpenGLExperiment", NULL, NULL);
	if (mWindow == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		//return -1;
	}

	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	glViewport(0, 0, mWidth, mHeight);

	//Using a lambda as the resize function for the callback
	glfwSetFramebufferSizeCallback(mWindow,
		[](GLFWwindow* window, int w, int h)
		{
			glViewport(0, 0, w, h);
		});

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

OpenGLContext::~OpenGLContext()
{
	glfwTerminate();
}

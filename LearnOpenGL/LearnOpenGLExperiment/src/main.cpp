//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include <OpenGLContext.h>
#include <Shader.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec4 vertexColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(aColor.r, aColor.g, aColor.b, 1.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\0";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	OpenGLContext oglContext(800,600);

	//Create data to render
	float vertices[]
	{   // position            //colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices[]
	{
		0, 1, 2,
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<const void*>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Shader stuff
	Shader shaderProgram("./shaders/basic.vert", "./shaders/basic.frag");


	while (!glfwWindowShouldClose(oglContext.GetWindow()))
	{
		//input
		processInput(oglContext.GetWindow());

		//Rendering
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw stuff
		shaderProgram.use();

		//update color
		float timeValue = glfwGetTime();
		//float redValue = (sin(timeValue) / 2.0f) + 0.5f;
		float xValue = sin(timeValue) / 2.0f;
		/*int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);*/
		shaderProgram.setUniform("position", xValue, 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
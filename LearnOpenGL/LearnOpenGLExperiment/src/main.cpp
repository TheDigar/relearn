//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include <OpenGLContext.h>
#include <Shader.h>
#include <Texture.h>

void processInput(GLFWwindow* window, float& mix)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if(mix < 1.0f)
			mix += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if(mix > 0.0f)
			mix -= 0.001f;
	}
}

int main()
{
	OpenGLContext oglContext(800,600);

	//Create data to render
	float vertices[]
	{   // position            //colors       //texture coordinates
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};

	unsigned int indices[]
	{
		0, 1, 2,
		2, 1, 3
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<const void*>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Shader program creation
	Shader shaderProgram("./shaders/basic.vert", "./shaders/basic.frag");

	//Load texture
	Texture tex1("./resources/wall.jpg");
	Texture tex2("./resources/awesomeface.png");

	//Tell opengl which texture unit each sampler belongs to
	shaderProgram.use();
	shaderProgram.setUniform("texture1", 0);
	shaderProgram.setUniform("texture2", 1);
	float mix = 0.2f;

	while (!glfwWindowShouldClose(oglContext.GetWindow()))
	{
		//input
		processInput(oglContext.GetWindow(), mix);

		//Rendering
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw stuff
		shaderProgram.use();

		//update color
		float timeValue = glfwGetTime();
		//float redValue = (sin(timeValue) / 2.0f) + 0.5f;
		float xValue = sin(timeValue/2.0f) / 2.0f;
		float yValue = sin(timeValue/4.0f) / 2.0f;
		/*int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);*/
		shaderProgram.setUniform("position", xValue, yValue, 0.0f, 0.0f);
		
		glActiveTexture(GL_TEXTURE0);
		tex1.bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.bind();
		shaderProgram.use();
		shaderProgram.setUniform("mixValue", mix);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
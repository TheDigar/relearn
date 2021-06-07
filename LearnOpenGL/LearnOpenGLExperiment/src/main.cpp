//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <OpenGLContext.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow* window,  Camera& camera, const float& deltaTime)
{
	//Window input
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//Camera input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.Move(Camera_Movement::Forward, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.Move(Camera_Movement::Backward, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.Move(Camera_Movement::Left, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.Move(Camera_Movement::Right, deltaTime);
	}
}

int main()
{
	//Create window and OpenGl Context
	OpenGLContext oglContext(800,600);

	//Model
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<const void*>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Shader program creation
	Shader shaderProgram("./shaders/basic.vert", "./shaders/basic.frag");

	//Load textures
	Texture tex1("./resources/wall.jpg");
	Texture tex2("./resources/awesomeface.png");

	//Tell opengl which texture unit each sampler belongs to
	shaderProgram.use();
	shaderProgram.setUniform("texture1", 0);
	shaderProgram.setUniform("texture2", 1);
	float mix = 0.2f;
	
	//Building matrices
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), -90.0f, 0.0f, 45.0f, static_cast<float>(oglContext.GetWidth() / oglContext.GetHeight()));
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));


	float lastFrameTime = glfwGetTime();
	double lastMouseX, lastMouseY;
	glfwGetCursorPos(oglContext.GetWindow(), &lastMouseX, &lastMouseY);

	while (!glfwWindowShouldClose(oglContext.GetWindow()))
	{
		//Update time
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		//Input Handling
		processInput(oglContext.GetWindow(), camera, deltaTime);
		double mouseX, mouseY;
		glfwGetCursorPos(oglContext.GetWindow(), &mouseX, &mouseY);
		camera.Tilt(mouseX - lastMouseX, lastMouseY - mouseY);
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));

		//Rendering
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw stuff
		shaderProgram.use();

		glActiveTexture(GL_TEXTURE0);
		tex1.Bind();
		glActiveTexture(GL_TEXTURE1);
		tex2.Bind();
		shaderProgram.setUniform("mixValue", mix);

		glBindVertexArray(VAO);

		//Transforms
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model*trans));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Transforms2
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		//trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model*trans));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
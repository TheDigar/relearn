//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <OpenGLContext.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <Model.h>
#include <SceneObject.h>

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
	Camera camera(glm::vec3(-2.5f, 1.5f, -1.5f), 42.0f, -25.0f, 45.0f, static_cast<float>(oglContext.GetWidth() / oglContext.GetHeight()));

	Model box;

	//Light object creation
	Shader whiteShaderProgram("./shaders/Lamp.vert", "./shaders/Lamp.frag");
	SceneObject lightObject(&box, &whiteShaderProgram);
	lightObject.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	lightObject.SetPosition(glm::vec3(1.2f, 1.0f, 2.0f));
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	whiteShaderProgram.use();
	whiteShaderProgram.setUniformMatrix4("projection", 1, false, glm::value_ptr(camera.GetProjection()));
	whiteShaderProgram.setUniform("lightColor", lightColor);
	
	//Box object creation
	Shader shaderProgram("./shaders/MaterialPhong.vert", "./shaders/MaterialPhong.frag");
	SceneObject boxObject(&box, &shaderProgram);
	boxObject.SetPosition(glm::vec3(-0.5f, -0.5f, 0.0f));
	boxObject.SetYaw(40.0f);

	//Tell opengl which texture unit each sampler belongs to
	shaderProgram.use();
	shaderProgram.setUniformMatrix4("projection", 1, false, glm::value_ptr(camera.GetProjection()));
	//material properties
	shaderProgram.setUniform("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	shaderProgram.setUniform("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	shaderProgram.setUniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shaderProgram.setUniform("material.shininess", 32.0f);
	//light properties
	shaderProgram.setUniform("light.ambient", glm::vec3(0.2f));
	shaderProgram.setUniform("light.diffuse", glm::vec3(0.5f));
	shaderProgram.setUniform("light.specular", glm::vec3(1.0f));


	double lastFrameTime = glfwGetTime();
	double lastMouseX, lastMouseY;
	glfwGetCursorPos(oglContext.GetWindow(), &lastMouseX, &lastMouseY);


	while (!glfwWindowShouldClose(oglContext.GetWindow()))
	{
		//Update time
		double currentTime = glfwGetTime();
		float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		//Input Handling
		processInput(oglContext.GetWindow(), camera, deltaTime);
		double mouseX, mouseY;
		glfwGetCursorPos(oglContext.GetWindow(), &mouseX, &mouseY);
		camera.Tilt(mouseX - lastMouseX, lastMouseY - mouseY);
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		//Clear the background to cornflower blue and clear the depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		whiteShaderProgram.use();
		whiteShaderProgram.setUniformMatrix4("view", 1, false, glm::value_ptr(camera.GetView()));

		//lightObject.SetPosition(glm::vec3(sin(currentTime)*2.0f, 2.0f, cos(currentTime)*2.0f));
		lightObject.Draw(camera);

		//Draw stuff
		shaderProgram.use();
		shaderProgram.setUniformMatrix4("view", 1, false, glm::value_ptr(camera.GetView()));
		shaderProgram.setUniform("lightPos", lightObject.GetPosition());
		shaderProgram.setUniform("viewPos", camera.GetPosition());


		boxObject.Draw(camera);



		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
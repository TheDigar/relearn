//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <filesystem>

#include <OpenGLContext.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>
#include <Model.h>
#include <SceneObject.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

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
	Camera camera(glm::vec3(4.0f, -0.5f, 5.0f), -120, 7.0f, 45.0f, static_cast<float>(oglContext.GetWidth() / oglContext.GetHeight()));
	
	stbi_set_flip_vertically_on_load(true);

	Shader shaderProgram("./shaders/ModelLoad.vert", "./shaders/ModelLoad.frag");


	Model ourModel("./resources/backpack/backpack.obj");

	shaderProgram.use();
	shaderProgram.setUniformMatrix4("projection", 1, false, glm::value_ptr(camera.GetProjection()));
	//material properties
	//shaderProgram.setUniform("material.diffuse", 0);
	//shaderProgram.setUniform("material.specular", 1);
	//shaderProgram.setUniform("material.emission", 2);
	//shaderProgram.setUniform("material.shininess", 32.0f);
	////light properties
	//shaderProgram.setUniform("pointLights.ambient", glm::vec3(0.2f));
	//shaderProgram.setUniform("pointLights.diffuse", glm::vec3(0.5f));
	//shaderProgram.setUniform("pointLights.specular", glm::vec3(1.0f));
	//shaderProgram.setUniform("pointLights.constant", 1.0f);
	//shaderProgram.setUniform("pointLights.linear", 0.09f);
	//shaderProgram.setUniform("pointLights.quadratic", 0.032f);
	//shaderProgram.setUniform("light.innerCutOff", glm::cos(glm::radians(12.5f)));
	//shaderProgram.setUniform("light.outerCutOff", glm::cos(glm::radians(17.5f)));


	double lastFrameTime = glfwGetTime();
	double lastMouseX, lastMouseY;
	glfwGetCursorPos(oglContext.GetWindow(), &lastMouseX, &lastMouseY);

	glEnable(GL_DEPTH_TEST);

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
		glClearColor(0.05f, 0.05f, 0.505f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw stuff
		shaderProgram.use();
		shaderProgram.setUniformMatrix4("view", 1, false, glm::value_ptr(camera.GetView()));
		//shaderProgram.setUniform("light.direction", glm::vec4(-0.2f, -1.0f, -0.3f ,0.0f));
		//shaderProgram.setUniform("pointLights.position", camera.GetView()*glm::vec4(0.5f,0.5f,0.5f, 1.0f));
		//shaderProgram.setUniform("viewPos", camera.GetPosition());

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		shaderProgram.setUniformMatrix4("model", 1, false, glm::value_ptr(model));

		ourModel.Draw(shaderProgram);




		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
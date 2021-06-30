//This order matters as glad.h already includes OpenGL headers ahead of glfw3...
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>

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
	

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader shaderProgram("./shaders/MaterialPhong.vert", "./shaders/MaterialPhongFlashlight.frag");

	std::list<SceneObject*> objects;
	for (unsigned int i = 0; i < 10; i++)
	{
		SceneObject* object = new SceneObject(&box, &shaderProgram);
		object->SetPosition(cubePositions[i]);
		float angle = 20.0f * i;
		object->SetYaw(angle);
		object->SetPitch(angle / 13.0f);
		objects.push_back(object);
	}
	//Box object creation
	Texture diffuseMap("./resources/container2.png");
	Texture specularMap("./resources/container2_specular.png");
	//Texture emissionMap("./resources/matrix.jpg");

	shaderProgram.use();
	shaderProgram.setUniformMatrix4("projection", 1, false, glm::value_ptr(camera.GetProjection()));
	//material properties
	shaderProgram.setUniform("material.diffuse", 0);
	shaderProgram.setUniform("material.specular", 1);
	shaderProgram.setUniform("material.emission", 2);
	shaderProgram.setUniform("material.shininess", 32.0f);
	//light properties
	shaderProgram.setUniform("light.ambient", glm::vec3(0.2f));
	shaderProgram.setUniform("light.diffuse", glm::vec3(0.5f));
	shaderProgram.setUniform("light.specular", glm::vec3(1.0f));
	shaderProgram.setUniform("light.constant", 1.0f);
	shaderProgram.setUniform("light.linear", 0.09f);
	shaderProgram.setUniform("light.quadratic", 0.032f);
	shaderProgram.setUniform("light.constant", 1.0f);
	shaderProgram.setUniform("light.linear", 0.09f);
	shaderProgram.setUniform("light.quadratic", 0.032f);
	shaderProgram.setUniform("light.innerCutOff", glm::cos(glm::radians(12.5f)));
	shaderProgram.setUniform("light.outerCutOff", glm::cos(glm::radians(17.5f)));


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

		lightObject.SetPosition(glm::vec3(sin(currentTime)*2.0f, 2.0f, cos(currentTime)*2.0f));
		lightObject.Draw(camera);

		//Draw stuff
		shaderProgram.use();
		shaderProgram.setUniformMatrix4("view", 1, false, glm::value_ptr(camera.GetView()));
		//shaderProgram.setUniform("light.direction", glm::vec4(-0.2f, -1.0f, -0.3f ,0.0f));
		shaderProgram.setUniform("light.direction", glm::vec4(camera.GetFront(), 1.0f));
		shaderProgram.setUniform("viewPos", camera.GetPosition());
		glActiveTexture(GL_TEXTURE0);
		diffuseMap.Bind();
		glActiveTexture(GL_TEXTURE1);
		specularMap.Bind();
		//glActiveTexture(GL_TEXTURE2);
		//emissionMap.Bind();

		for (auto object : objects)
		{
			object->Draw(camera);
		}




		//check and call events and swap buffers 
		glfwPollEvents();
		glfwSwapBuffers(oglContext.GetWindow());
	}

	return 0;
}
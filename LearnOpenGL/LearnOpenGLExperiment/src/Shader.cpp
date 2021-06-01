#include "Shader.h"

#include <glad\glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::ifstream shaderFile;
	//Ensure exceptions on ifstream
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	//Vertex Shader
	std::string shaderCode;
	try
	{
		shaderFile.open(vertexShaderPath);
		std::stringstream buffer;
		buffer << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = buffer.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::VERTEX_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	//Compile shader
	const char* vertexShaderSource = shaderCode.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//Check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	//Fragment Shader
	try
	{
		shaderFile.open(fragmentShaderPath);
		std::stringstream buffer;
		buffer << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = buffer.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::FRAGMENT_SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	//Compile shader
	const char* fragmentShaderSource = shaderCode.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Check for errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	//Shader program stuff
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setUniform(const std::string uniformName, float v1, float v2, float v3, float v4)
{
	int uniformLocation = glGetUniformLocation(ID, uniformName.c_str());
	glUniform4f(uniformLocation, v1, v2, v3, v4);
}

void Shader::setUniform(const std::string uniformName, int v1)
{
	int uniformLocation = glGetUniformLocation(ID, uniformName.c_str());
	glUniform1i(uniformLocation, v1);
}

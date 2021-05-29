#pragma once

#include <string>

class Shader
{
private:
	//Shader program ID
	unsigned int ID;

public:
	//Creates a program witha vertex and fragment shader
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	//use shader
	void use();
	void setUniform(const std::string uniformName, float v1, float v2, float v3, float v4);
};


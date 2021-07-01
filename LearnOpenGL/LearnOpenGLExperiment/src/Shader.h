#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Shader
{
public:
	//Shader program ID
	unsigned int ID;

public:
	//Creates a program witha vertex and fragment shader
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();

	//use shader
	void use();
	void setUniform(const std::string uniformName, float v1, float v2, float v3, float v4);
	void setUniform(const std::string uniformName, const glm::vec4& vec);
	void setUniform(const std::string uniformName, float v1, float v2, float v3);
	void setUniform(const std::string uniformName, const glm::vec3& vec);
	void setUniform(const std::string uniformName, float v1);
	void setUniform(const std::string uniformName, int v1);
	void setUniformMatrix4(const std::string uniformName, int n, bool transpose, float* data);
	void setUniformMatrix3(const std::string uniformName, int n, bool transpose, float* data);
};


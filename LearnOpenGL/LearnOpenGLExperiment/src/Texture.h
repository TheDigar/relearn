#pragma once

#include <glad/glad.h>

class Texture
{
private:
	unsigned int ID;

public:
	Texture(const char* texturePath, 
		GLenum wrapS = GL_REPEAT,
		GLenum wrapT= GL_REPEAT, 
		GLenum minFilter = GL_LINEAR, 
		GLenum magFilter = GL_LINEAR);
	void Bind();
};


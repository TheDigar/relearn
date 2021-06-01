#pragma once

#include <glad/glad.h>

class Texture
{
private:
	unsigned int ID;

public:
	Texture(const char* texturePath, GLenum wrapS = GL_REPEAT, GLenum wrapT= GL_REPEAT);
	void bind();
};


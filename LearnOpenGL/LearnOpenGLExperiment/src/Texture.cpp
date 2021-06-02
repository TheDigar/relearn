#include "Texture.h"
#include <glad/glad.h>

#include <stb_image.h>
#include <iostream>

Texture::Texture(const char* texturePath, GLenum wrapS, GLenum wrapT, GLenum minFilter,	GLenum magFilter)
{
	//Load texture file
	int width;
	int height;
	int nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath, &width, &height, &nChannels, 0);

	//Crete and bind OpenGL Texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	//Set wraping and filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
			(nChannels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//We can release the image now
	stbi_image_free(data);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

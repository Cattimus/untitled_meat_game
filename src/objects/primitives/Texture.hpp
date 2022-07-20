#pragma once

#include "glad/glad.h"
#include <iostream>

class Texture
{
private:
	unsigned int id;
	int width;
	int height;
	int channels;

public:
	Texture(std::string filename, GLenum type);

	~Texture()
	{
		glDeleteTextures(1, &id);
	}

	void use()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	float aspect_ratio()
	{
		return (float)width / height;
	}

	double get_width()
	{
		return width;
	}

	double get_height()
	{
		return height;
	}

	double get_channels()
	{
		return channels;
	}
};
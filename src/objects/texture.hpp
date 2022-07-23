#pragma once

#include "glad/glad.h"
#include "imgui.h"
#include <iostream>
#include <vector>

class Texture
{
private:
	unsigned int id;
	int width;
	int height;
	int channels;
	std::string name;
	std::string filename;

public:

	Texture(std::string filename, GLenum type, std::string name);

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

	int get_width()
	{
		return width;
	}

	int get_height()
	{
		return height;
	}

	int get_channels()
	{
		return channels;
	}

	std::string get_name()
	{
		return name;
	}

	std::string get_filename()
	{
		return filename;
	}

	unsigned int get_id()
	{
		return id;
	}
};
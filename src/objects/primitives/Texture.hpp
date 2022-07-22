#pragma once

#include "glad/glad.h"
#include "imgui.h"
#include <iostream>

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

	std::string get_name()
	{
		return name;
	}

	//info for debug
	void debug_frame()
	{
		if(ImGui::TreeNode(name.c_str()))
		{
			ImGui::Text("Filename: %s", filename.c_str());
			ImGui::Text("Width: %d", width);
			ImGui::Text("Height: %d", height);
			ImGui::Text("Channels: %d", channels);
			ImGui::Text("Address: %p", this);
			ImGui::Text("Opengl Texture ID: %d", id);
			ImGui::TreePop();
		}
	}
};
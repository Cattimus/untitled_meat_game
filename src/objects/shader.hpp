#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include <iostream>

class Shader
{
private:
	unsigned int id; //unique ID given to shader by opengl
	bool valid; //flag to detect if something has gone wrong during shader compilation
	std::string name;

	unsigned int compile_shader(const char* shader, GLenum type);

public:
	Shader(std::string vert, std::string frag, std::string name);

	//free resources
	~Shader()
	{
		glDeleteProgram(id);
	}

	//use shader for rendering
	void use()
	{
		glUseProgram(id);
	}

	std::string get_name()
	{
		return name;
	}

	bool is_valid()
	{
		return valid;
	}

	unsigned int get_id()
	{
		return id;
	}

	void set_1i(std::string name, int value)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	void set_1f(std::string name, float value)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void set_vec3f(std::string name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
	}

	void set_vec3f(std::string name, const glm::vec3 &data)
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), data.x, data.y, data.z);
	}

	void set_mat4f(std::string name, const glm::mat4 &data)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &data[0][0]);
	}
};
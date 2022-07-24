#include "shader.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <vector>
#include "references.hpp"

unsigned int Shader::compile_shader(const char* shader, GLenum type)
{
	//compile shader
	unsigned int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader, NULL);
	glCompileShader(shader_id);

	//check shader compilation
	int success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	//print errors if compilation fails
	if (!success)
	{
		char log[1024];
		glGetShaderInfoLog(shader_id, 1024, NULL, log);

		//helps to understand where the error is occuring
		if(type == GL_VERTEX_SHADER)
		{
			std::cout << "vertex ";
		}
		else
		{
			std::cout << "fragment ";
		}
		std::cout << "shader compilation failed!\n" << log << std::endl;
		return 0;
	}

	return shader_id;
}

Shader::Shader(std::string vert, std::string frag, std::string name)
{
	this->name = name;
	unsigned int vert_id;
	unsigned int frag_id;

	std::stringstream vert_text;
	std::stringstream frag_text;

	//read files to strings
	try
	{
		std::ifstream vert_stream(vert);
		std::ifstream frag_stream(frag);

		vert_text << vert_stream.rdbuf();
		frag_text << frag_stream.rdbuf();

		vert_stream.close();
		frag_stream.close();
	}

	//failure to read files
	catch (const std::ifstream::failure& e)
	{
		std::cout << "Shader: Failure to open/read file - " << e.what() << std::endl;
		id = 0;
		valid = false;
		return;
	}
	
	valid = true;

	//compile fragment and vertex shader
	vert_id = compile_shader(vert_text.str().c_str(), GL_VERTEX_SHADER);
	frag_id = compile_shader(frag_text.str().c_str(), GL_FRAGMENT_SHADER);

	//compile shader program
	id = glCreateProgram();
	glAttachShader(id, vert_id);
	glAttachShader(id, frag_id);
	glLinkProgram(id);

	//check compilation success
	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success)
	{
		char log[1024];
		glGetProgramInfoLog(id, 1024, NULL, log);
		std::cout << "Shader: failed to link shader.\n" << log << std::endl;
		valid = false;
	}

	//free resources
	glDeleteShader(vert_id);
	glDeleteShader(frag_id);

	References::shaders.push_back(this);
}
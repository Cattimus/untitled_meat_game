#pragma once

#include "data/movement.hpp"
#include "data/mesh.hpp"
#include "data/shader.hpp"
#include "data/texture.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <vector>
#include <iostream>
#include "references.hpp"

class Shader;
class Texture;
class Entity;

class Entity : public Movement
{
private:
	Mesh mesh;
	Shader* shader;
	Texture* texture;
	std::string name;

public:
	Entity(Shader* objShader, Texture* objTexture, std::string objName)
	{
		shader = objShader;
		texture = objTexture;
		name = objName;
		References::objects.push_back(this);
	}
	
	//render the current object
	void render()
	{
		update_position();
		shader->set_mat4f("model", get_model());
		texture->use();
		mesh.draw();
	}

	Shader* get_shader()
	{
		return shader;
	}

	Mesh* get_mesh()
	{
		return &mesh;
	}

	void set_shader(Shader* to)
	{
		shader = to;
	}

	Texture* get_texture()
	{
		return texture;
	}
	
	void set_texture(Texture* to)
	{
		texture = to;
	}

	std::string get_name()
	{
		return name;
	}
};
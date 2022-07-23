#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <vector>

class Shader;
class Texture;
class Entity;

class Entity : public Position
{
private:
	Mesh mesh;
	Shader* shader;
	Texture* texture;
	std::string name;

public:
	static std::vector<Entity*> objects;

	Entity(Shader* objShader, Texture* objTexture, std::string objName)
	{
		shader = objShader;
		texture = objTexture;
		name = objName;
		objects.push_back(this);
	}
	
	//render the current object
	void render()
	{
		texture->use();
		mesh.draw();
	}

	//adds the appropriate debug info to the debug UI frame
	void debug_frame();
};
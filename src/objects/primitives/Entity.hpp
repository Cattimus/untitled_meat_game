#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
//also needs a texture

class Entity
{
private:
	Mesh mesh;
	Shader* shader;
	//Texture texture

public:
	Position position;
	glm::vec3 render_color;

	Entity(Shader* objShader)
	{
		render_color = glm::vec3(0.4f, 0.2f, 0.6f);
		shader = objShader;
	}
	
	//render the current object
	void render()
	{
		shader->use();
		shader->set_vec3f("inColor", render_color);
		mesh.draw();
	}
};

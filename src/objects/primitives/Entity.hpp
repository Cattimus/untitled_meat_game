#pragma once

#include "Position.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
//also needs a texture

class Entity : public Position
{
private:
	Mesh mesh;
	Shader* shader;
	//Texture texture

public:
	glm::vec3 render_color;

	Entity(Shader* objShader)
	{
		render_color = glm::vec3(0.4f, 0.2f, 0.6f);
		shader = objShader;
	}
	
	//render the current object
	void render()
	{
		shader->set_vec3f("inColor", render_color);
		mesh.draw();
	}
};
